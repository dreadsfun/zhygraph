#pragma once
class i_scene_node;

class i_graphics {
public:
	virtual bool initialize( void ) = 0;
	virtual void update_scene( i_scene_node* root ) = 0;
};

class i_window_closed_listener {
public:
	virtual void respond( void ) = 0;
};

class i_update_listener {
public:
	virtual void respond( double dt ) = 0;
};

class i_initialization_end_listener {
public:
	virtual void respond( void ) = 0;
};