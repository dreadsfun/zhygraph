#include "consume_di.hpp"
#include <di/di.hxx>
#include <di/di-pimpl.hxx>
xml_configuration::xml_configuration(void * data, size_t size)
	: m_data(data),
	m_size(size),
	m_owns(false) {}

xml_configuration::xml_configuration(const std::string & fnm)
	: m_owns(true) {
	struct stat b;
	if (stat(fnm.c_str(), &b) != 0) {
		throw std::exception((fnm + " was not found to load the configurationn").c_str());
	}
	if (b.st_size > 0) {
		FILE* f = nullptr;
		fopen_s(&f, fnm.c_str(), "rb");
		m_data = malloc(b.st_size);
		fread_s(m_data, b.st_size, sizeof(char), b.st_size, f);
		m_size = b.st_size;
		fclose(f);
	}
}

xml_configuration::~xml_configuration(void)
{
	if (m_owns) {
		free(m_data);
	}
}

void xml_configuration::parse(void)
{
	if (m_data != nullptr) {
		DI_paggr di_p;
		xml_schema::document_pimpl doc_p(di_p.root_parser(), di_p.root_name());
		di_p.pre();
		doc_p.parse(m_data, m_size, true);
		m_pdi = di_p.post();
	}
	else {
		throw std::exception("Parser data was not initialized.");
	}
}

void xml_configuration::fill(di::component_registry & c)
{
	if (m_pdi->plugins_present()) {
		for (const shared& s : m_pdi->plugins().shared()) {
			try {
				di::plugin::load(s.lib());
			}
			catch (const di::library_failed_to_load& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	for (const component& p : m_pdi->components().component()) {
		try {
			di::component* nc = c.create(p.name(), p.class_());
			for (const attribute_type& at : p.attribute()) {
				if (at.value_present()) {
					_set_attrib(nc, at.name(), at.value());
				}
				else {
					for (const insert& i : at.insert()) {
						_set_attrib(nc, at.name(), i.value());
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	for (const inject& it : m_pdi->wiring().inject()) {
		try {
			c.use(it.injection()).as(it.slot()).of(it.receiver());
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	for (const inject_all& ia : m_pdi->wiring().inject_all()) {
		auto inj = c.get_component(ia.injection());
		for (const inject_all_type& iat : ia.inject()) {
			try {
				c.use(inj).as(iat.slot()).of(iat.receiver());
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	for (const inject_one& io : m_pdi->wiring().inject_one()) {
		auto inj = c.get_component(io.receiver());
		for (const inject_one_type& iot : io.inject()) {
			try {
				c.use(iot.injection()).as(iot.slot()).of(inj);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	for (const inject_slot& is : m_pdi->wiring().inject_slot()) {
		di::component* inj = c.get_component(is.injection());
		for (const auto& pp : c) {
			try {
				pp.second->inject(is.slot(), inj);
			}
			catch (const di::dependency_not_found&) {}
		}
	}
}

void xml_configuration::_set_attrib(di::component * cmp, const std::string & n, const std::string & v)
{
	try {
		cmp->set_attribute(n, v);
	}
	catch (const di::wrong_type&) {
		std::cerr << "Failed to set attribute named \"" << n << "\" to value \"" << v << "\", \
				because the value string is not convertible to the defined type of the attribute." << std::endl;
	}
	catch (const di::attribute_not_found&) {
		std::cerr << "Failed to set attribute named \"" << n << "\" to value \"" << v << "\", \
				because the named attribute was not found" << std::endl;
	}
}
