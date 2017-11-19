#include <di_rtlib\register_class.hpp>
#include <di_rtlib\component.hpp>
#include <core\scripting.hpp>
#include <core\system_base.hpp>
#include <python\Python.h>
class py_scripting
	: public system_base, public i_scripting {
public:
	virtual bool initialize() {
		Py_Initialize();
		FILE* pylibfile = nullptr;
		fopen_s( &pylibfile, "py_api\\lib.py", "r" );
		if( pylibfile == nullptr ) {
			serror << "failed to open python library file";
		} else {
			PyRun_SimpleFile( pylibfile, "lib.py" );
			fclose( pylibfile );
		}
		
		return true;
	}

	virtual void update_scene( i_scene_node* root ) {

	}

	virtual void _process_scene( i_scene_node* root, node_subscription& ns );
	virtual node_subscription create_subscription( void );
};


void py_scripting::_process_scene( i_scene_node* root, node_subscription& ns ) { }

node_subscription py_scripting::create_subscription( void ) {
	return node_subscription();
}

register_class( py_scripting );