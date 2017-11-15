#include "scene_node.hpp"
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

void scene_node_base::reload( bool async ) {
	bool exp = true;
	if( m_loaded.compare_exchange_strong( exp, false ) ) {
		this->lock();
		this->_unload( m_type_manager );
		this->_load( m_type_manager, async );
		m_loaded = true;
		this->unlock();
	}
}

void scene_node_base::lock( void ) {
	m_node_mutex.lock();
}

bool scene_node_base::try_lock( void ) {
	return m_node_mutex.try_lock();
}

void scene_node_base::unlock( void ) {
	m_node_mutex.unlock();
}

scene_node_base::transform & scene_node_base::get_transform( void ) {
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

void scene_node_base::update( node_subscription & ns ) { }

void scene_node_base::load( type_manager_ptr p, bool async ) {
	m_type_manager = p;
	m_loaded = this->_load( m_type_manager, async );
}

void scene_node_base::unload( type_manager_ptr p ) {
	if( m_loaded ) {
		this->_unload( p );
		m_loaded = false;
	}
}

const glm::vec3 scene_node_base::transform::up;
const glm::vec3 scene_node_base::transform::down;
const glm::vec3 scene_node_base::transform::left;
const glm::vec3 scene_node_base::transform::right;
const glm::vec3 scene_node_base::transform::forward;
const glm::vec3 scene_node_base::transform::backward;