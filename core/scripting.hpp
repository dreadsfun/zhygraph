#pragma once

class i_scene_node;

class i_scripting {
public:
	virtual bool initialize( void ) = 0;
	virtual void update_scene( i_scene_node* root ) = 0;
};