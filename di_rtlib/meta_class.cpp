#include "meta_class.hpp"
#include "exception.hpp"
#include "component.hpp"
namespace di {
meta_class class_registry::get_meta_class( const std::string& name ) {
	meta_class r;
	auto fit = instance->m_classes.find( name );
	if( fit == instance->m_classes.end() ) throw class_not_found( name );
	r = fit->second;
	return r;
}

component* class_registry::create( const std::string& cn ) {
	meta_class m = get_meta_class( cn );
	component* nc = m.invoke_ctor();
	nc->set_meta_class( m );
	return nc;
}

component* class_registry::create( const std::string& cn, meta_class& mc ) {
	mc = get_meta_class( cn );
	component* nc = mc.invoke_ctor();
	nc->set_meta_class( mc );
	return nc;
}

class_registry* class_registry::instance = new class_registry();

meta_class::meta_class( const std::string& name, constructor_t ctor )
	: m_name( name ),
	m_constructor( ctor ) { }

component* meta_class::invoke_ctor( void ) {
	component* r = nullptr;
	if( m_constructor ) r = m_constructor();
	return r;
}

const std::string& meta_class::get_class_name( void ) const {
	return m_name;
}
}
