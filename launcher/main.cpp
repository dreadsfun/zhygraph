#include <iostream>
#include "consume_di.hpp"
#include "launcher.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif //~_WIN32
#include "main.h"
#include <thread>
#include <di_rtlib/component_registry.hpp>
int _lch( void ) {
	int r = 0;
	try {
		xml_configuration con( "engine.conf" );
		con.parse();
		di::component_registry c;
		con.fill( c );
		c.initialize_components();

		i_launcher* l = c.get_< i_launcher >( "engine_launcher" );
		l->run();

		c.purge();

	} catch( const std::exception& e ) {
#ifdef _DEBUG
		std::cerr << e.what() << std::endl;
#endif // ~_DEBUG
#ifdef _WIN32
		MessageBoxA( NULL, e.what(), "ERROR", MB_ICONERROR | MB_OK );
#endif // ~_WIN32
		r = -1;
	}
	return r;
}

void* launcher_thread( void ) {
	return new std::thread( _lch );
}

int launcher( void ) {
	return _lch();
}