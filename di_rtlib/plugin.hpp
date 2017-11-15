#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "export.hpp"
namespace di {
class i_shared_library { };

class plugin {
private:
	typedef std::unique_ptr< i_shared_library > library_ptr;
	typedef std::shared_ptr< plugin > plugin_ptr;
	typedef std::unordered_map< std::string, plugin_ptr > plugin_map;

	static DI_SHARED plugin_map loaded_libraries;

	library_ptr m_library;

public:
	static DI_SHARED plugin_ptr load( const std::string& file ) {
		plugin_ptr r;
		auto fit = loaded_libraries.find( file );
		if( fit == loaded_libraries.end() ) {
			r = std::make_shared< plugin >();
			r->m_library = _create_library( file );
			loaded_libraries[ file ] = r;
		}
		return r;
	}

private:
	static DI_SHARED library_ptr _create_library( const std::string& file );
};
}