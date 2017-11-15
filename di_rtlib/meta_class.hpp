#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include "export.hpp"
namespace di {
class component;

class meta_class {
private:
	typedef component*( *constructor_t ) ( void );

	std::string m_name;
	constructor_t m_constructor;

public:
	DI_SHARED meta_class( void ) = default;
	DI_SHARED meta_class( const std::string& name, constructor_t ctor );
	DI_SHARED component* invoke_ctor( void );
	DI_SHARED const std::string& get_class_name( void ) const;
};

class class_registry {
private:
	std::unordered_map< std::string, meta_class > m_classes;

	static DI_SHARED class_registry* instance;

public:
	template< typename T >
	static void insert( const std::string& cn ) {
		auto fit = instance->m_classes.find( cn );
		if( fit == instance->m_classes.end() ) {
			auto ctor = []() -> component* {
				return static_cast< component* >( new T() );
			};
			instance->m_classes.emplace( cn, meta_class( cn, ctor ) );
		}
	}

	static DI_SHARED meta_class get_meta_class( const std::string& name );

	template< typename T >
	static T* create( const std::string& cn ) {
		return static_cast< T* >( create( cn ) );
	}

	template< typename T >
	static T* create( const std::string& cn, meta_class& mc ) {
		return static_cast< T* >( create( cn, mc ) );
	}

	static DI_SHARED component* create( const std::string& cn );
	static DI_SHARED component* create( const std::string& cn, meta_class& mc );
};
}