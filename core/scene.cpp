#include "scene.hpp"
#include <scene/scene.hxx>
scene_tree_parser::scene_tree_parser( const std::string & d )
	: m_desc( d ) { }

std::string scene_tree_parser::get_current( void ) const {
	return m_current;
}

void scene_tree_parser::step( void ) {
	size_t sp = m_desc.find( ' ', m_index );
	if( sp == std::string::npos ) {
		sp = m_desc.length();
	}
	m_current = m_desc.substr( m_index, sp - m_index );
	m_index = sp + 1;

	if( m_current == "." ) {
		m_token = tree_token::back;
	} else {
		m_token = tree_token::node;
	}
}

bool scene_tree_parser::has( void ) const {
	return m_index < m_desc.length();
}

scene_tree_parser::tree_token scene_tree_parser::get_token( void ) const {
	return m_token;
}

scene_tree::scene_tree( i_logger * l )
	: m_logger( l ) { }

void scene_tree::build( const scene & s, const nodes & ns ) { 
	m_name = s.name();

	if( s.graph_present() ) {
		scene_tree_parser p( s.graph() );

		i_scene_node* curr = nullptr;
		while( p.has() ) {

			p.step();

			if( p.get_token() == scene_tree_parser::tree_token::node ) {
				scene_node_ptr np = _create_node( p.get_current(), ns );
				if( np ) {
					m_nodes.push_back( np );
					i_scene_node* nch = m_nodes.back().get();
					if( curr != nullptr ) {
						curr->add_child( nch );
					}
					curr = nch;
				}
			}

			if( p.get_token() == scene_tree_parser::tree_token::back ) {
				if( curr != nullptr ) {
					curr = curr->get_parent();
				}
			}
		}
	}
}

void scene_tree::traverse_depth( node_visitor_ptr v ) {
	scene_node_ptr n = this->get_root();
	if( n ) {
		n->traverse_depth( v );
	}
}

void scene_tree::traverse_breadth( node_visitor_ptr v ) {
	scene_node_ptr n = this->get_root();
	if( n ) {
		n->traverse_breadth( v );
	}
}

const std::string & scene_tree::get_name( void ) const {
	return m_name;
}

scene_node_ptr scene_tree::get_root( void ) {
	scene_node_ptr r;
	if( m_nodes.size() > 0 ) {
		r = m_nodes.front();
	}
	return r;
}

scene_node_ptr scene_tree::_create_node( const std::string & n, const nodes & ns ) const {
	scene_node_ptr p;
	for( const node& nd : ns.node() ) {
		if( nd.name() == n ) {
			p = scene_node_ptr( static_cast< scene_node_base* >( di::class_registry::create( nd.class_() ) ) );
			if( p ) {
				p->set_name( n );

				if( nd.position_present() ) {
					p->get_transform().set_position( glm::vec3( nd.position().x(), nd.position().y(), nd.position().z() ) );
				}

				if( nd.rotation_present() ) {
					p->get_transform().set_rotation( glm::quat( nd.rotation().w(), nd.rotation().x(), nd.rotation().y(), nd.rotation().z() ) );
				}

				if( nd.scale_present() ) {
					p->get_transform().set_scale( glm::vec3( nd.scale().x(), nd.scale().y(), nd.scale().z() ) );
				}

				for( const attribute& a : nd.attribute() ) {
					try {
						p->set_attribute( a.name(), a.value() );
					} catch( std::exception& e ) {
						error( e.what() );
					}
				}
				sinfo << "created node: " << p->get_name() << " " << nd.class_();
			} else {
				serror << "failed to create node with name \"" << n << "\" and class \"" << nd.class_() << "\"";
			}
			break;
		}
	}
	return p;
}

bool scene_tree::is_loaded( void ) const {
	return m_loaded;
}

scene_manager_base::scene_tree_map scene_manager_base::get_available_scenes( void ) const {
	return m_scenes;
}

scene_manager_base::scene_tree_map scene_manager_base::get_loaded( void ) const {
	return m_loaded;
}