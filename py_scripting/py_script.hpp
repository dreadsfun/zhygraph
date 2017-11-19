#pragma once
#include <core/asset.hpp>
#include <python\Python.h>
class py_script
	: public asset_base {
private:
	std::string mdictname;
	PyObject* mscriptdict;
	PyObject* mupdatefunc;
	PyObject* minitfunc;

	static PyObject* globaldict;

public:
	py_script( const asset_url& url );



private:
	virtual bool load( const std::string& data, std::string& err ) override;
	virtual bool unload( std::string& err ) override;
};

using script_ptr = std::shared_ptr<py_script>;