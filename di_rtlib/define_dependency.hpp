#pragma once
#include "component.hpp"
static std::string _dependency_name( const std::string& ln ) {
	return ln.substr( 2, ln.size() - 2 );
}
#define component_dependency( name, type ) di::component::dependency< type > name { this->_create_id(), _dependency_name( #name ) }
#define component_dependencies( name, type ) di::component::dependencies< type > name { this->_create_id(), _dependency_name( #name ) }