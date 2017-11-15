#pragma once
#include "scripting.hpp"
#include "logger.hpp"
#include <di_rtlib/define_dependency.hpp>
#include <unordered_map>
class sd_script_context
	: di::component {
private:
	component_dependency( m_logger, i_logger );
	component_dependency( m_script_context, i_script_context );

	static sd_script_context* instance;

	std::unordered_map< const std::string*, std::string > m_node_names;

public:
	static bool store_attribute( const std::string* pnm, const std::string& attnm ) {
		instance->m_script_context->store_attribute( pnm, attnm );
	}

private:
	virtual void initialize_component( void ) override {
		if( instance == nullptr ) {
			instance = this;
		} else {
			warn( "script context static distributor created (or catalog init called) multiple times, only first istance is used" );
		}
	}
};

namespace test {
struct teststr {
	std::string fasz;
};
}

template< typename T >
class script_storage {
public:
	script_storage( const std::string* pnm, i_scene_node* owner ) {

	}
};