#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <queue>
#include <memory>
#include <vector>
#include "export.h"
namespace zhygraph {
	namespace core {
		class i_scene_node;

		class i_node_visitor {
		public:
			// visit the given node
			virtual void visit( i_scene_node* n ) = 0;
			// returns true if the purpose of this visitor
			// is achieved and the traversal should be halted
			// e.g. if it was used for a search, return true if
			// the searched node was found at some point
			virtual bool completed( void ) const = 0;
		};

		typedef std::shared_ptr< i_node_visitor > node_visitor_ptr;
		typedef std::vector< i_scene_node* > scene_node_vector;

		class i_scene_node {
		public:
			virtual std::string get_name( void ) const = 0;
			virtual void set_name( const std::string& n ) = 0;
			virtual i_scene_node* get_parent( void ) = 0;
			virtual scene_node_vector get_children( void ) = 0;
			virtual i_scene_node* get_root( void ) = 0;
			virtual void add_child( i_scene_node* n ) = 0;
			virtual void remove_child( i_scene_node* n ) = 0;
			virtual void set_parent( i_scene_node* n ) = 0;
			virtual void traverse_depth( node_visitor_ptr v ) = 0;
			virtual void traverse_breadth( node_visitor_ptr v ) = 0;
			virtual bool is_root( void ) const = 0;
		};

		class all_node_visitor
			: public i_node_visitor {
		private:
			virtual bool completed( void ) const override {
				return false;
			}
		};

		class scene_node_base;

		class transform {
		public:
			enum class space {
				world,
				self
			};

			static core_shared const glm::vec3 up;
			static core_shared const glm::vec3 down;
			static core_shared const glm::vec3 left;
			static core_shared const glm::vec3 right;
			static core_shared const glm::vec3 forward;
			static core_shared const glm::vec3 backward;

		private:
			scene_node_base* m_owner;

			glm::vec3 m_position;
			glm::quat m_rotation;
			glm::vec3 m_scale { 1.0f, 1.0f, 1.0f };

			bool m_dirty_tr { true };
			bool m_dirty_itr { true };

			glm::mat4 m_world;
			glm::mat4 m_local;

			void _set_dirty( void );

			glm::mat4 _calculate_local_transform( void ) {
				glm::mat4 trans;
				trans[ 3 ] = glm::vec4( m_position, 1.0f );
				glm::mat4 rot( m_rotation );
				glm::mat4 sc;
				sc[ 0 ][ 0 ] = m_scale.x;
				sc[ 1 ][ 1 ] = m_scale.y;
				sc[ 2 ][ 2 ] = m_scale.z;
				return trans * rot * sc;
			}

		public:
			transform( scene_node_base* ow )
				: m_owner( ow ) { }

			glm::vec3 get_local_position( void ) const {
				return m_position;
			}

			void set_local_position( const glm::vec3& v ) {
				m_position = v;
			}

			glm::quat get_local_rotation( void ) const {
				return m_rotation;
			}

			void set_local_rotation( const glm::quat& v ) {
				m_rotation = v;
			}

			glm::vec3 get_local_scale( void ) const {
				return m_scale;
			}

			void set_local_scale( const glm::vec3& v ) {
				m_scale = v;
			}

			const glm::mat4& get_world_matrix( void );

			const glm::mat4& get_local_matrix( void ) {
				if( m_dirty_itr ) {
					m_local = glm::inverse( this->get_world_matrix() );
					m_dirty_itr = false;
				}
				return m_local;
			}

			glm::vec3 get_position( void ) {
				return glm::vec3( this->get_world_matrix() * glm::vec4( m_position, 1.0f ) );
			}

			void set_position( const glm::vec3& p );

			glm::quat get_rotation( void ) {
				static glm::quat grot;
				if( m_dirty_tr ) {
					grot = glm::quat_cast( this->get_world_matrix() );
				}
				return grot;
			}

			void set_rotation( const glm::quat& r );

			glm::vec3 get_scale( void ) {
				static glm::vec3 gsc;
				if( m_dirty_tr ) {
					const glm::mat4& m = this->get_world_matrix();
					gsc = glm::vec3( m[ 0 ][ 0 ], m[ 1 ][ 1 ], m[ 2 ][ 2 ] ) * m_scale;
				}
				return gsc;
			}

			void set_scale( const glm::vec3& s );

			glm::vec3 get_local_euler_angles( void ) const {
				return glm::eulerAngles( m_rotation );
			}

			void set_local_euler_angles( const glm::vec3& e ) {
				m_rotation = from_euler( e );
				_set_dirty();
			}

			static glm::quat from_euler( const glm::vec3& e ) {
				float t0 = glm::cos( e.x * 0.5f );
				float t1 = glm::sin( e.x * 0.5f );
				float t2 = glm::cos( e.z * 0.5f );
				float t3 = glm::sin( e.z * 0.5f );
				float t4 = glm::cos( e.y * 0.5f );
				float t5 = glm::sin( e.y * 0.5f );
				glm::quat r;
				r.w = t0 * t2 * t4 + t1 * t3 * t5;
				r.x = t0 * t3 * t4 - t1 * t2 * t5;
				r.y = t0 * t2 * t5 + t1 * t3 * t4;
				r.z = t1 * t2 * t4 - t0 * t3 * t5;
				return r;
			}

			bool has_changed( void ) const {
				return m_dirty_tr;
			}

			void translate( const glm::vec3& dir, space s ) {
				glm::vec4 tp( dir, 1.0f );
				if( s == space::self ) {
					tp = glm::vec4( this->transform_direction( dir ), 1.0f );
				}
				glm::mat4 trans;
				trans[ 3 ] = tp;
				m_position = glm::vec3( trans * glm::vec4( m_position, 1.0f ) );
				_set_dirty();
			}

			void rotate_around( const glm::vec3& c, const glm::vec3& ax, float ang, bool look = false ) {
				const glm::quat rot = glm::angleAxis( ang, ax );
				this->set_position( c + rot * ( this->get_position() - c ) );
				if( look ) {
					this->set_rotation( rot * this->get_rotation() );
				}
				_set_dirty();
			}

			void rotate( const glm::vec3& euler, space s ) {
				if( s == space::self ) {
					m_rotation = from_euler( euler ) * m_rotation;
				} else {
					this->set_rotation( from_euler( euler ) * m_rotation );
				}
				_set_dirty();
			}

			void look_at( transform& tar, const glm::vec3& up ) {
				this->set_rotation( glm::quat( glm::lookAt( this->get_position(), tar.get_position(), up ) ) );
			}

			glm::vec3 inverse_transform_position( const glm::vec3& p ) {
				return glm::vec3( this->get_local_matrix() * glm::vec4( p, 1.0f ) );
			}

			glm::vec3 inverse_transform_direction( const glm::vec3& d ) {
				return glm::normalize( glm::vec3( glm::transpose( this->get_world_matrix() ) * glm::vec4( d, 0.0f ) ) );
			}

			glm::vec3 transform_position( const glm::vec3& p ) {
				return glm::vec3( this->get_world_matrix() * glm::vec4( p, 1.0f ) );
			}

			glm::vec3 transform_direction( const glm::vec3& d ) {
				return glm::normalize( glm::vec3( glm::inverse( glm::transpose( this->get_world_matrix() ) ) * glm::vec4( d, 0.0f ) ) );
			}

			void set_up( const glm::vec3& u ) {
				m_rotation = glm::rotation( this->get_up(), u ) * m_rotation;
				_set_dirty();
			}

			glm::vec3 get_up( void ) {
				return this->transform_direction( up );
			}
		};

		class scene_node_base
			: public i_scene_node {
		public:
			typedef std::queue< i_scene_node* > scene_node_queue;

		protected:
			std::string m_name;
			transform m_transform;
			i_scene_node* m_parent { nullptr };
			scene_node_vector m_children;

		protected:
			scene_node_base( const std::string& d );

		public:
			core_shared scene_node_base( void );
			core_shared transform& get_transform( void );
			virtual core_shared std::string get_name( void ) const override;
			virtual core_shared void set_name( const std::string& n ) override;
			virtual core_shared i_scene_node* get_parent( void ) override;
			virtual core_shared scene_node_vector get_children( void ) override;
			virtual core_shared i_scene_node* get_root( void ) override;
			virtual core_shared void add_child( i_scene_node* n ) override;
			virtual core_shared void remove_child( i_scene_node* n ) override;
			virtual core_shared void set_parent( i_scene_node* n ) override;
			virtual core_shared void traverse_depth( node_visitor_ptr v ) override;
			virtual core_shared void traverse_breadth( node_visitor_ptr v ) override;
			virtual core_shared bool is_root( void ) const override;
			core_shared void* operator new( size_t s );
			core_shared void operator delete( void* p );
		};

		typedef std::shared_ptr< scene_node_base > scene_node_ptr;
	}
}
