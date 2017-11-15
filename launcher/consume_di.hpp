#pragma once
#include <string>
#include <di_rtlib/component_registry.hpp>
#include <di_rtlib/plugin.hpp>

// forward declare from <di/di.hxx>
class DI;

class xml_configuration {
private:
	DI* m_pdi { nullptr };
	void* m_data { nullptr };
	size_t m_size;
	bool m_owns;

public:
	xml_configuration(void* data, size_t size);
	xml_configuration(const std::string& fnm);
	~xml_configuration(void);
	void parse(void);
	void fill(di::component_registry& c);

private:
	void _set_attrib(di::component* cmp, const std::string& n, const std::string& v);
};