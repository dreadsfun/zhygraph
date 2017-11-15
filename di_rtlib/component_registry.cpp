#include "component_registry.hpp"
#include "exception.hpp"
namespace di {
void component_registry::purge( void ) {
	for( auto& pp : m_components ) {
		pp.second.release();
	}
}
component* component_registry::get_component( const std::string& id ) {
	component* r = nullptr;
	auto fit = m_components.find( id );
	if( fit == m_components.end() ) throw component_not_found( id );
	r = fit->second.get();
	return r;
}

component* component_registry::create( const std::string& id, const std::string& clname ) {
	component* r = nullptr;
	auto fit = m_components.find( id );
	if( fit != m_components.end() ) throw component_already_exists( id, clname );
	r = class_registry::create< component >( clname );
	if( r != nullptr ) {
		m_components.emplace( id, std::move( std::unique_ptr< component >( r ) ) );
	}
	return r;
}

void component_registry::initialize_components( void ) {
	for( const auto& pp : m_components ) {
		pp.second->initialize_component();
	}
}
}
