#include <di_rtlib\register_class.hpp>
#include "py_script.hpp"
py_script::py_script( const asset_url& url )
	: asset_base( url ) { }

bool py_script::load( const std::string& data, std::string& err ) {
	if( !globaldict ) {
		PyObject* mainmodule = PyImport_AddModule( "__main__" );
		globaldict = PyModule_GetDict( mainmodule );
	}

	mscriptdict = PyDict_New();
	mdictname = this->get_path().get_path('.');
	PyDict_SetItemString( globaldict, mdictname.c_str(), mscriptdict );

	if( PyRun_String( data.c_str(), Py_file_input, mscriptdict, mscriptdict ) ) {
		mupdatefunc = PyDict_GetItemString( mscriptdict, "update" );
		minitfunc = PyDict_GetItemString( mscriptdict, "init" );
		return true;
	} else {
		err = "error when running PyRun_String";
		return false;
	}
}

bool py_script::unload( std::string& err ) {
	if( globaldict ) {
		PyDict_DelItemString( globaldict, mdictname.c_str() );
		Py_DECREF( mscriptdict );
	}
	return true;
}

PyObject* py_script::globaldict = nullptr;


class py_script_manager
	: public asset_manager_base {
private:
	virtual const char* get_type() const override {
		return "script";
	}

	virtual asset_ptr create_asset( const asset_url& url ) override {
		return std::make_shared< py_script >( url );
	}
};

register_class( py_script_manager );