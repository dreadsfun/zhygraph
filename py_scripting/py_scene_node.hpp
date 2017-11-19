#pragma once
#include <core/scene_node.hpp>
#include "py_script.hpp"
class py_scene_node
	: public scene_node_base {
private:
	component_attribute( m_script_url, std::string );

	script_ptr mscript;

	virtual bool _load( type_manager_ptr tm, bool async );
	virtual void _unload( type_manager_ptr p );
	virtual void update( node_subscription& ns ) override;
};