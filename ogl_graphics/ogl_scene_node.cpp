#include "ogl_scene_node.hpp"
asset::mesh_ptr mesh_renderer_node::get_mesh( void ) {
	return m_mesh;
}

const mesh_renderer_node::material_vector & mesh_renderer_node::get_materials( void ) const {
	return m_materials.get_values();
}

const mesh_renderer_node::texture_map_vector & mesh_renderer_node::get_textures( void ) const {
	return m_textures;
}

bool mesh_renderer_node::_load( type_manager_ptr tm, bool async ) {
	asset_url murl( m_mesh_url );
	asset_manager_ptr mgr = tm->get( "mesh" );
	asset_manager_ptr tmgr = tm->get( "texture" );

	for( const std::string& mat : m_materials ) {
		const material* mmod = material_library::get_material( mat );
		if( mmod != nullptr && mmod->texture().size() > 0 ) {
			bool growtxmap = true;
			for( const texture& t : mmod->texture() ) {
				asset::texture_ptr tptr = std::static_pointer_cast< asset::texture >( tmgr->get_asset( asset_url( t.file() ) ) );
				if( tptr ) {
					if( growtxmap ) {
						m_textures.emplace_back();
						growtxmap = false;
					}
					m_textures.back().insert( std::make_pair( t.sampler(), tptr ) );
				}
			}
		}
	}

	m_mesh = std::static_pointer_cast< asset::mesh >( mgr->get_asset( murl ) );
	if( async ) {
		mgr->load_asset( murl, nullptr );
		for( const texture_map& mp : m_textures ) {
			for( const auto& pp : mp ) {
				tmgr->load_asset( pp.second->get_path(), nullptr );
			}
		}
	} else {
		mgr->load_asset( murl );
		for( const texture_map& mp : m_textures ) {
			for( const auto& pp : mp ) {
				tmgr->load_asset( pp.second->get_path() );
			}
		}
	}

	return static_cast< bool >( m_mesh );
}

void mesh_renderer_node::_unload( type_manager_ptr p ) {
	m_mesh.reset();
	m_textures.clear();
	m_textures.swap( decltype( m_textures )( ) );
}

void mesh_renderer_node::update( node_subscription & ns ) {
	if( m_loaded ) ns.subscribe_as( "mesh_renderer", this );
}

glm::mat4 camera_node::get_mvp( const glm::mat4 & model ) {
	if( this->get_transform().has_changed() ) {
		m_view_projection_matrix = m_projection_matrix * this->get_transform().get_world_matrix();
	}
	return m_view_projection_matrix * model;
}

const glm::mat4 & camera_node::get_projection( void ) const {
	return m_projection_matrix;
}

void camera_node::begin_screen( int width, int height ) {
	glViewport( static_cast< int >( m_viewport_x * width ), static_cast< int >( m_viewport_y * height ),
		static_cast< int >( m_viewport_width * width ), static_cast< int >( m_viewport_height * height ) );
}

bool camera_node::_load( type_manager_ptr tm, bool async ) {
	_update_to_projection_mode();
	return true;
}

void camera_node::update( node_subscription & ns ) { 
	ns.subscribe_as( "camera", this );
}

void camera_node::_update_to_projection_mode( void ) {
	if( m_projection_mode.get_value() == "perspective" ) {
		m_projection_matrix = glm::perspective< float >( m_field_of_view, m_aspect_ratio, m_near_clip, m_far_clip );
	} else {
		m_projection_matrix = glm::ortho< float >( m_left, m_right, m_bottom, m_top, m_near_clip, m_far_clip );
	}
}

#include <di_rtlib/register_class.hpp>
register_class( mesh_renderer_node );
register_class( camera_node );