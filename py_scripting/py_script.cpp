#include <di_rtlib\register_class.hpp>
#include "py_script.hpp"
py_script::py_script( const asset_url& url )
	: asset_base( url ) { }

void py_script::callupdatescript( std::string& error ) {
	if( mupdatefunc && !PyObject_CallObject( mupdatefunc, nullptr ) )
		_checkfillerror( error );
}

void py_script::callinitscript( std::string& error ) {
	if( minitfunc && !PyObject_CallObject( minitfunc, nullptr ) )
		_checkfillerror( error );
}

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
		_checkfillerror( err );
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

void py_script::_checkfillerror( std::string& error ) { 
	if( PyErr_Occurred() != NULL ) {
		PyObject *pyExcType;
		PyObject *pyExcValue;
		PyObject *pyExcTraceback;
		PyErr_Fetch( &pyExcType, &pyExcValue, &pyExcTraceback );
		PyErr_NormalizeException( &pyExcType, &pyExcValue, &pyExcTraceback );

		PyObject* str_exc_type = PyObject_Repr( pyExcType );
		PyObject* pyStr = PyUnicode_AsEncodedString( str_exc_type, "utf-8", "Error ~" );
		const char *strExcType = PyBytes_AS_STRING( pyStr );

		PyObject* str_exc_value = PyObject_Repr( pyExcValue );
		PyObject* pyExcValueStr = PyUnicode_AsEncodedString( str_exc_value, "utf-8", "Error ~" );
		const char *strExcValue = PyBytes_AS_STRING( pyExcValueStr );

		error = std::string( strExcType ) + " " + strExcValue;

		// When using PyErr_Restore() there is no need to use Py_XDECREF for these 3 pointers
		//PyErr_Restore(pyExcType, pyExcValue, pyExcTraceback);

		Py_XDECREF( pyExcType );
		Py_XDECREF( pyExcValue );
		Py_XDECREF( pyExcTraceback );

		Py_XDECREF( str_exc_type );
		Py_XDECREF( pyStr );

		Py_XDECREF( str_exc_value );
		Py_XDECREF( pyExcValueStr );
	}
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