#pragma once
#include "../core/graphics.hpp"
#include "../core/scene_node.hpp"
#include "ogl_asset.hpp"
#include "material_library.hpp"
class mesh_renderer_node
	: public scene_node_base {
private:
	typedef std::unordered_map< std::string, asset::texture_ptr > texture_map;
	typedef std::vector< texture_map > texture_map_vector;
	typedef std::vector< std::string > material_vector;

	component_attribute( m_mesh_url, std::string );
	component_attributes( m_materials, std::string );

	asset::mesh_ptr m_mesh;
	texture_map_vector m_textures;

public:
	asset::mesh_ptr get_mesh( void );
	const material_vector& get_materials( void ) const;
	const texture_map_vector& get_textures( void ) const;

private:
	virtual void _load( type_manager_ptr tm, bool async );
	virtual void _unload( type_manager_ptr p );
	virtual void update( node_subscription& ns ) override;
};

#include "../di_rtlib/define_attribute.hpp"
class camera_node
	: public scene_node_base {
private:
	component_attribute( m_projection_mode, std::string );
	component_attribute( m_field_of_view, float );
	component_attribute( m_aspect_ratio, float );
	component_attribute( m_left, float );
	component_attribute( m_right, float );
	component_attribute( m_bottom, float );
	component_attribute( m_top, float );
	component_attribute( m_near_clip, float );
	component_attribute( m_far_clip, float );
	component_attribute( m_viewport_x, float );
	component_attribute( m_viewport_y, float );
	component_attribute( m_viewport_width, float );
	component_attribute( m_viewport_height, float );

	glm::mat4 m_projection_matrix;
	glm::mat4 m_view_projection_matrix;

public:
	glm::mat4 get_mvp( const glm::mat4& model );
	const glm::mat4& get_projection( void ) const;
	void begin_screen( int width, int height );

private:
	virtual void _load( type_manager_ptr tm, bool async ) override;
	virtual void update( node_subscription& ns ) override;
	void _update_to_projection_mode( void );
};