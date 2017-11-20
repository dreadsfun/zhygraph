#include "py_scene_node.hpp"

bool py_scene_node::_load( type_manager_ptr tm, bool async ) {
	asset_manager_ptr scriptmanager = tm->get( "script" );
	bool r = false;
	if( scriptmanager ) {
		asset_ptr scriptasset = scriptmanager->load_asset( asset_url( m_script_url ) );
		if( scriptasset ) {
			mscript = std::static_pointer_cast< py_script >( scriptasset );
			r = true;
		}
	}
	return r;
}

void py_scene_node::_unload( type_manager_ptr p ) { 
	mscript.reset();
}

void py_scene_node::update( node_subscription& ns ) {
	if( m_loaded ) ns.subscribe_as( "script", this );
}

void py_scene_node::callupdatescript( std::string& error ) {
	mscript->callupdatescript( error );
}

#include <di_rtlib\register_class.hpp>
register_class( py_scene_node );