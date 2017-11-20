#include <di_rtlib\register_class.hpp>
#include <di_rtlib\component.hpp>
#include <core\scripting.hpp>
#include <core\system_base.hpp>
#include <python\Python.h>
#include <fstream>
#include "py_scene_node.hpp"
class py_scripting
	: public system_base, public i_scripting {
public:
	virtual bool initialize() {
		Py_Initialize();

	/*	std::ifstream libfile( "py_api\\lib.py", std::ios::ate );
		if( libfile.is_open() ) {
			std::string libdata( libfile.tellg(), '0' );
			libfile.seekg( 0, std::ios::beg );
			libfile.read( &libdata[ 0 ], libdata.size() );

			PyObject* mainmodule = PyImport_AddModule( "__main__" );
			PyObject* globaldict = PyModule_GetDict( mainmodule );

			PyRun_String( libdata.c_str(), Py_file_input, globaldict, globaldict );

			libfile.close();
		} else {
			serror << "failed to open python library file";
			return false;
		}*/

		//PyObject* libmodule = PyImport_ImportModule( "py_api.lib" );
		
		return true;
	}

	virtual void update_scene( i_scene_node* root ) {
		this->process_scene( root );
	}

	virtual void _process_scene( i_scene_node* root, node_subscription& ns ) {
		node_subscription::node_range_iterator_pair scripts = ns.get_subscribers( "script" );
		for( auto script = scripts.first; script != scripts.second; ++script ) {
			py_scene_node* scriptnode = static_cast< py_scene_node* >( script->second );
			std::string error;
			scriptnode->callupdatescript( error );
			if( !error.empty() )
				serror << error;
		}
	}

	virtual node_subscription create_subscription( void ) {
		node_subscription ns;
		ns.allow_name( "script" );
		return ns;
	}
};

register_class( py_scripting );