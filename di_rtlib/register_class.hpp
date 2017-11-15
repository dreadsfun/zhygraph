#pragma once
#include "meta_class.hpp"
namespace di {
template< typename T >
class class_registrator {
public:
	class_registrator( const std::string& cl ) {
		class_registry::insert< T >( cl );
	}
};
#define register_class( clname ) static ::di::class_registrator< clname > __register_ ##clname ##__ { #clname }
}