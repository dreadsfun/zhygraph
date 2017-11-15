#include "component.hpp"
namespace di {
void component::inject( const std::string& dep, component* cmp ) {
	auto fit = m_dependencies.find( dep );
	if( fit == m_dependencies.end() ) throw dependency_not_found( dep, m_meta.get_class_name() );
	fit->second->set_component( cmp );
}

std::string component::get_attribute( const std::string& name ) const {
	std::string r;
	auto fit = m_attributes.find( name );
	if( fit == m_attributes.end() ) throw attribute_not_found( name, m_meta.get_class_name() );
	r = fit->second->format_string();
	return r;
}
}