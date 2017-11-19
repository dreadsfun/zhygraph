#pragma once
#include <memory>
#include <vector>
#include <string>
#include "export.hpp"
#include "scene_node.hpp"
#include "logger.hpp"
class scene_tree_parser {
#pragma region types
public:
	enum class tree_token {
		node,
		back
	};
#pragma endregion

#pragma region data members
private:
	std::string m_desc;
	std::string m_current;
	tree_token m_token { tree_token::node };
	size_t m_index { 0 };
#pragma endregion

#pragma region member functions
public:
	scene_tree_parser( const std::string& d );
	std::string get_current( void ) const;
	void step( void );
	bool has( void ) const;
	tree_token get_token( void ) const;
#pragma endregion
};

#include <di_rtlib/meta_class.hpp>

// forward declare from <scene/scene.hxx> to reduce header dependency
class scene;
class nodes;

class scene_tree {
#pragma region types
private:
	typedef std::vector< scene_node_ptr > node_vector;
#pragma endregion
	
#pragma region data members
private:
	std::string m_name;
	node_vector m_nodes;
	bool m_loaded { false };
	i_logger* m_logger { nullptr };
#pragma endregion

#pragma region member functions
public:
	CORE_SHARED scene_tree( i_logger* l );
	CORE_SHARED bool is_loaded( void ) const;
	CORE_SHARED void build( const scene& s, const nodes& ns );
	CORE_SHARED void traverse_depth( i_node_visitor& v );
	CORE_SHARED void traverse_breadth( i_node_visitor& v );
	CORE_SHARED const std::string& get_name( void ) const;
	CORE_SHARED scene_node_ptr get_root( void );

private:
	scene_node_ptr _create_node( const std::string& n, const nodes& ns ) const;
#pragma endregion
};

typedef std::shared_ptr< scene_tree > scene_tree_ptr;

class i_scene_manager {
public:
	virtual std::unordered_map< std::string, scene_tree_ptr > get_available_scenes( void ) const = 0;
	virtual bool load_first( void ) = 0;
	virtual bool load_scene( const std::string& n, bool async ) = 0;
	virtual bool load_scene_additive( const std::string& n, bool async ) = 0;
	virtual std::unordered_map< std::string, scene_tree_ptr > get_loaded( void ) const = 0;
	virtual void update( double dt ) = 0;
};

#include <di_rtlib/define_attribute.hpp>
#include <di_rtlib/define_dependency.hpp>
#include "asset.hpp"
class scene_manager_base
	: public i_scene_manager, public di::component {
#pragma region types
private:
	typedef std::unordered_map< std::string, scene_tree_ptr > scene_tree_map;
#pragma endregion

#pragma region data members
protected:
	component_dependency( m_type_manager, i_asset_type_manager );
	component_dependency( m_logger, i_logger );
	component_attribute( m_scene_file, std::string );
	scene_tree_map m_scenes;
	scene_tree_map m_loaded;
#pragma endregion

#pragma region member functions
private:
	virtual scene_tree_map get_available_scenes( void ) const override;
	virtual scene_tree_map get_loaded( void ) const override;

public:
	virtual bool load_first( void ) = 0;
	virtual bool load_scene( const std::string& n, bool async ) = 0;
	virtual bool load_scene_additive( const std::string& n, bool async ) = 0;
	virtual void update( double dt ) = 0;
#pragma endregion
};