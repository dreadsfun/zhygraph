#pragma once
#include <exception>
#include <string>
namespace di {
class named_element_exception
	: public std::exception {
protected:
	std::string m_name;
	std::string m_class;
	std::string m_what;

public:
	named_element_exception( const std::string& name, const std::string& cl )
		: m_name( name ),
		m_class( cl ) { }

	virtual const char* what( void ) const override sealed {
		return m_what.c_str();
	}

	const std::string& get_name( void ) const {
		return m_name;
	}

	const std::string& get_class( void ) const {
		return m_class;
	}
};

class component_already_exists
	: public named_element_exception {
public:
	component_already_exists( const std::string& id, const std::string& cl )
		: named_element_exception( id, cl ) {
		m_what = "component with id \"" + id + "\" already exists as class \"" + cl + "\"";
	}
};

class component_not_found
	: public named_element_exception {
public:
	component_not_found( const std::string& name )
		: named_element_exception( name, "" ) {
		m_what = "component named \"" + name + "\" was not found in registry";
	}
};

class class_not_found
	: public named_element_exception {
public:
	class_not_found( const std::string& name )
		: named_element_exception( name, name ) {
		m_what = "class \"" + name + "\" was not found as a registered class";
	}
};

class attribute_not_found
	: public named_element_exception {
public:
	attribute_not_found( const std::string& name, const std::string& cl )
		: named_element_exception( name, cl ) {
		m_what = "class \"" + cl + "\" has no attribute, named \"" + name + "\"";
	}
};

class dependency_not_found
	: public named_element_exception {
public:
	dependency_not_found( const std::string& name, const std::string& rcl )
		: named_element_exception( name, rcl ) {
		m_what = "class \"" + rcl + "\" has no dependency, named \"" + name + "\"";
	}
};

class wrong_type
	: public named_element_exception {
public:
	wrong_type( const std::string& name, const std::string& cl )
		: named_element_exception( name, cl ) {
		m_what = "attribute named \"" + name + "\" in class \"" + cl + "\" was provided wrong data type";
	}
};

class slot_not_found
	: public named_element_exception {
public:
	slot_not_found( const std::string& name, const std::string& cl )
		: named_element_exception( name, cl ) {
		m_what = "dependency slot named \"" + name + "\" was not found in class \"" + cl + "\"";
	}
};

class library_failed_to_load
	: public named_element_exception {
public:
	library_failed_to_load( const std::string& name, const std::string& reason = "" )
		: named_element_exception( name, "" ) {
		m_what = "library named \"" + name + "\" failed to load" + ( reason.empty() ? "" : ", reason: " + reason );
	}
};
}