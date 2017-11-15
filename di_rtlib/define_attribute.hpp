#pragma once
#include "component.hpp"
static std::string _attribute_name( const std::string& ln ) {
	return ln.substr( 2, ln.size() - 2 );
}
#define component_attribute( name, type, ... ) di::component::attribute< type > name { this->_create_id(), _attribute_name( #name ), __VA_ARGS__  }
#define component_attributes( name, type ) di::component::attributes< type > name { this->_create_id(), _attribute_name( #name ) }