#pragma once
#include <core/asset.hpp>
#include <python\Python.h>
class py_script
	: public asset_base {
private:
	std::string mdictname;
	PyObject* mscriptdict { nullptr };
	PyObject* mupdatefunc { nullptr };
	PyObject* minitfunc { nullptr };

	static PyObject* globaldict;

public:
	py_script( const asset_url& url );

	void callupdatescript(std::string& error);
	void callinitscript(std::string& error);

	static void printstacktrace(std::string& trace);

private:
	virtual bool load( const std::string& data, std::string& err ) override;
	virtual bool unload( std::string& err ) override;

	void _checkfillerror( std::string& error );
};

using script_ptr = std::shared_ptr<py_script>;