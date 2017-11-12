#include <core.zhygraph\approot.h>
#include <iostream>
#include <exception>
int main( int argc, char** argv ) {
	try {
		zhygraph::core::application_root app( "assets.ini", "config.ini", "scenes.sc" );
		app.initialize();
		app.run();
	} catch( const std::exception& e ) {
		std::cerr << e.what();
		return -1;
	}
	return 0;
}