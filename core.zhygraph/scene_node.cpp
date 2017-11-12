#include "scene_node.h"
namespace zhygraph {
	namespace core {
		scene_node_base::scene_node_base( const std::string & d )
			: m_name( d ),
			m_transform( this ) { }

		scene_node_base::scene_node_base( void )
			: m_transform( this ) { }

		void * scene_node_base::operator new( size_t s ) {
			return _aligned_malloc( s, alignof( scene_node_base ) );
		}

		void scene_node_base::operator delete( void * p ) {
			_aligned_free( p );
		}

		transform & scene_node_base::get_transform( void ) {
			return m_transform;
		}

		std::string scene_node_base::get_name( void ) const {
			return m_name;
		}

		void scene_node_base::set_name( const std::string & n ) {
			m_name = n;
		}

		i_scene_node * scene_node_base::get_parent( void ) {
			return m_parent;
		}

		scene_node_vector scene_node_base::get_children( void ) {
			return m_children;
		}

		i_scene_node * scene_node_base::get_root( void ) {
			i_scene_node* c = this;
			for( ; c->get_parent(); c = c->get_parent() );
			return c;
		}

		void scene_node_base::add_child( i_scene_node * n ) {
			bool is = false;
			for( i_scene_node*& c : m_children ) {
				if( !c ) {
					c = n;
					is = true;
					break;
				}
			}

			if( !is ) {
				m_children.push_back( n );
			}

			n->set_parent( this );
		}

		void scene_node_base::remove_child( i_scene_node * n ) {
			for( i_scene_node*& c : m_children ) {
				if( c == n ) {
					c = nullptr;
					break;
				}
			}
		}

		void scene_node_base::set_parent( i_scene_node * n ) {
			if( m_parent ) {
				m_parent->remove_child( this );
			}
			m_parent = n;
		}

		void scene_node_base::traverse_depth( node_visitor_ptr v ) {
			v->visit( this );
			// this branch ensures that no more
			// child is traversed at the current depth if the visitor is complete
			if( !v->completed() ) {
				for( i_scene_node* p : m_children ) {
					p->traverse_depth( v );
					// this break ensures that no more DEPTH
					// is traversed if the visitor is complete
					if( v->completed() ) break;

				}
			}
		}

		void scene_node_base::traverse_breadth( node_visitor_ptr v ) {
			scene_node_queue q;
			q.push( this );
			while( !q.empty() ) {
				// visit current node
				v->visit( q.front() );
				// do no more discover nor visit if the visitor is completed with
				// the previous visit
				if( v->completed() ) break;
				scene_node_vector cdr = q.front()->get_children();
				for( i_scene_node* c : cdr ) {
					// discover adjacent nodes
					q.push( c );
				}
				q.pop();
			}
		}

		bool scene_node_base::is_root( void ) const {
			return !m_parent;
		}

		const glm::vec3 transform::up;
		const glm::vec3 transform::down;
		const glm::vec3 transform::left;
		const glm::vec3 transform::right;
		const glm::vec3 transform::forward;
		const glm::vec3 transform::backward;

		void transform::_set_dirty( void ) {
			if( !m_dirty_tr ) {
				m_dirty_tr = true;
				m_dirty_itr = true;
				for( i_scene_node* n : m_owner->get_children() ) {
					static_cast< scene_node_base* >( n )->get_transform()._set_dirty();
				}
			}
		}

		const glm::mat4 & transform::get_world_matrix( void ) {
			if( m_dirty_tr ) {
				if( m_owner->get_parent() == nullptr ) {
					m_world = _calculate_local_transform();
				} else {
					m_world = static_cast< scene_node_base* >( m_owner->get_parent() )->
						get_transform().get_world_matrix() * _calculate_local_transform();
				}
			}
			return m_world;
		}

		void transform::set_position( const glm::vec3& p ) {
			if( m_owner->get_parent() == nullptr ) {
				m_position = p;
			} else {
				m_position = p - static_cast< scene_node_base* >( m_owner->get_parent() )->get_transform().get_position();
			}
			_set_dirty();
		}

		void transform::set_rotation( const glm::quat & r ) {
			if( m_owner->get_parent() == nullptr ) {
				m_rotation = r;
			} else {
				m_rotation = glm::inverse( static_cast< scene_node_base* >( m_owner->get_parent() )->get_transform().get_rotation() ) * r;
			}
			_set_dirty();
		}
		void transform::set_scale( const glm::vec3 & s ) {
			if( m_owner->get_parent() == nullptr ) {
				m_scale = s;
			} else {
				m_scale = s / static_cast< scene_node_base* >( m_owner->get_parent() )->get_transform().get_scale();
			}
			_set_dirty();
		}
	}
}