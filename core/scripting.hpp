#pragma once

class i_scene_node;

#include <string>
#include <vector>

class i_script_context {
public:
	virtual bool store_attribute( const std::string* pnm, const std::string& attnm );
};



class script_context {
private:

};

class i_scripting {
public:
	virtual void initialize( void ) = 0;
	virtual void update_scene( i_scene_node* root ) = 0;
	virtual std::shared_ptr< i_script_context > create_context( void ) = 0;
};