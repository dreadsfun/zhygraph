#include "capi.h"
#include <core/logger.hpp>
#include <core/scene.hpp>
#include <core/windowing.hpp>
template< typename T >
class handle {
private:
	T* m_obj { nullptr };

public:
	handle( long long h )
		: m_obj( reinterpret_cast< T* >( h ) ) { }

	static long long cast( T* h ) {
		return reinterpret_cast< long long >( h );
	}

	T* operator -> ( void ) {
		return m_obj;
	}

	T* operator * ( void ) {
		return m_obj;
	}
};

class capi_bridge
	: public di::component {
private:
	virtual void initialize_component( void ) override {
		if( instance == nullptr ) {
			instance = this;
		}
	}

public:
	static capi_bridge* instance;

	component_dependency( m_logger, i_logger );
	component_dependency( m_scene_manager, i_scene_manager );
	component_dependency( m_windowing, i_windowing_library );
};

capi_bridge* capi_bridge::instance = nullptr;


class scene_node_finder
	: public i_node_visitor {
private:
	std::string m_name;
	bool m_completed;
	i_scene_node* m_result;

public:
	void set_name( const std::string& n ) {
		m_name = n;
		m_completed = false;
		m_result = nullptr;
	}

	i_scene_node* get_result( void ) {
		return m_result;
	}

private:
	virtual void visit( i_scene_node* n ) override {
		if( n->get_name() == m_name ) {
			m_completed = true;
			m_result = n;
		}
	}

	virtual bool completed( void ) const override {
		return m_completed;
	}
};

#include <di_rtlib/register_class.hpp>
register_class( capi_bridge );

#include <Windows.h>

#pragma region input
int keys_backspace = VK_BACK;
int keys_tab = VK_TAB;
int keys_clear = VK_CLEAR;
int keys_return = VK_RETURN;
int keys_shift = VK_SHIFT;
int keys_control = VK_CONTROL;
int keys_alt = VK_MENU;
int keys_pause = VK_PAUSE;
int keys_capital = VK_CAPITAL;
int keys_escape = VK_ESCAPE;
int keys_space = VK_SPACE;
int keys_prior = VK_PRIOR;
int keys_next = VK_NEXT;
int keys_end = VK_END;
int keys_home = VK_HOME;
int keys_left = VK_LEFT;
int keys_up = VK_UP;
int keys_right = VK_RIGHT;
int keys_down = VK_DOWN;
int keys_select = VK_SELECT;
int keys_print = VK_PRINT;
int keys_execute = VK_EXECUTE;
int keys_snapshot = VK_SNAPSHOT;
int keys_insert = VK_INSERT;
int keys_delete = VK_DELETE;
int keys_help = VK_HELP;

int keys_leftwin = VK_LWIN;
int keys_rightwin = VK_RWIN;
int keys_apps = VK_APPS;
int keys_sleep = VK_SLEEP;

int keys_numpad0 = VK_NUMPAD0;
int keys_numpad1 = VK_NUMPAD1;
int keys_numpad2 = VK_NUMPAD2;
int keys_numpad3 = VK_NUMPAD3;
int keys_numpad4 = VK_NUMPAD4;
int keys_numpad5 = VK_NUMPAD5;
int keys_numpad6 = VK_NUMPAD6;
int keys_numpad7 = VK_NUMPAD7;
int keys_numpad8 = VK_NUMPAD8;
int keys_numpad9 = VK_NUMPAD9;

int keys_multiply = VK_MULTIPLY;
int keys_add = VK_ADD;
int keys_separator = VK_SEPARATOR;
int keys_subtract = VK_SUBTRACT;
int keys_decimal = VK_DECIMAL;
int keys_divide = VK_DIVIDE;

int keys_f1 = VK_F1;
int keys_f2 = VK_F2;
int keys_f3 = VK_F3;
int keys_f4 = VK_F4;
int keys_f5 = VK_F5;
int keys_f6 = VK_F6;
int keys_f7 = VK_F7;
int keys_f8 = VK_F8;
int keys_f9 = VK_F9;
int keys_f10 = VK_F10;
int keys_f11 = VK_F11;
int keys_f12 = VK_F12;
int keys_f13 = VK_F13;
int keys_f14 = VK_F14;
int keys_f15 = VK_F15;

int keys_numlock = VK_NUMLOCK;
int keys_scroll = VK_SCROLL;

int keys_leftshift = VK_LSHIFT;
int keys_rightshift = VK_RSHIFT;
int keys_leftcontrol = VK_LCONTROL;
int keys_rightcontrol = VK_RCONTROL;
int keys_leftmenu = VK_LMENU;
int keys_rightmenu = VK_RMENU;

int keys_volmute = VK_VOLUME_MUTE;
int keys_voldown = VK_VOLUME_DOWN;
int keys_volup = VK_VOLUME_UP;

int keys_0 = 0x30;
int keys_1 = 0x31;
int keys_2 = 0x32;
int keys_3 = 0x33;
int keys_4 = 0x34;
int keys_5 = 0x35;
int keys_6 = 0x36;
int keys_7 = 0x37;
int keys_8 = 0x38;
int keys_9 = 0x39;

int keys_a = 0x41;
int keys_b = 0x42;
int keys_c = 0x43;
int keys_d = 0x44;
int keys_e = 0x45;
int keys_f = 0x46;
int keys_g = 0x47;
int keys_h = 0x48;
int keys_i = 0x49;
int keys_j = 0x4A;
int keys_k = 0x4B;
int keys_l = 0x4C;
int keys_m = 0x4D;
int keys_n = 0x4E;
int keys_o = 0x4F;
int keys_p = 0x50;
int keys_q = 0x51;
int keys_r = 0x52;
int keys_s = 0x53;
int keys_t = 0x54;
int keys_u = 0x55;
int keys_v = 0x56;
int keys_w = 0x57;
int keys_x = 0x58;
int keys_y = 0x59;
int keys_z = 0x5A;

int buttons_left = VK_LBUTTON;
int buttons_right = VK_RBUTTON;
int buttons_middle = VK_MBUTTON;
int buttons_extra1 = VK_XBUTTON1;
int buttons_extra2 = VK_XBUTTON2;
#pragma endregion

#pragma region input classsss
bool input_get_key_down( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_key_down( key );
}

bool input_get_key_up( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_key_up( key );
}

bool input_get_key( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_key( key );
}

bool input_get_button_down( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_mouse_down( key );
}

bool input_get_button_up( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_mouse_up( key );
}

bool input_get_button( int key ) {
	return capi_bridge::instance->m_windowing->get_input_manager()->get_mouse( key );
}

prvec< 2 >::strc input_get_cursor_position( void ) {
	ddvec2 v = capi_bridge::instance->m_windowing->get_input_manager()->get_cursor_position();
	prvec< 2 >::strc r;
	r.d[ 0 ] = static_cast< float >( v.x );
	r.d[ 1 ] = static_cast< float >( v.y );
	return r;
}
prvec< 2 >::strc input_get_cursor_displacement( void ) {
	ddvec2 v = capi_bridge::instance->m_windowing->get_input_manager()->get_cursor_displacement();
	prvec< 2 >::strc r;
	r.d[ 0 ] = static_cast< float >( v.x );
	r.d[ 1 ] = static_cast< float >( v.y );
	return r;
}
#pragma endregion


#pragma region log class
void log_debug( const char* msg ) {
	capi_bridge::instance->m_logger->log( priority::debug, msg, "capi_bridge" );
}

void log_info( const char* msg ) {
	capi_bridge::instance->m_logger->log( priority::info, msg, "capi_bridge" );
}

void log_warn( const char* msg ) {
	capi_bridge::instance->m_logger->log( priority::warn, msg, "capi_bridge" );
}

void log_error( const char* msg ) {
	capi_bridge::instance->m_logger->log( priority::error, msg, "capi_bridge" );
}
#pragma endregion


#pragma region transform
scene_node_base::transform::space _trspace( int s ) {
	return s == 0 ? scene_node_base::transform::space::world : scene_node_base::transform::space::self;
}

template< unsigned int i, typename T >
typename prvec< i >::strc _proxyv( const T& v );

template< unsigned int i, typename T >
T _proxyv( const typename prvec< i >::strc& v );

template<>
prvec< 2 >::strc _proxyv< 2, glm::vec2 >( const glm::vec2& v ) {
	prvec< 2 >::strc r;
	r.d[ 0 ] = v.x;
	r.d[ 1 ] = v.y;
	return r;
}

template<>
prvec< 3 >::strc _proxyv< 3, glm::vec3 >( const glm::vec3& v ) {
	prvec< 3 >::strc r;
	r.d[ 0 ] = v.x;
	r.d[ 1 ] = v.y;
	r.d[ 2 ] = v.z;
	return r;
}

template<>
prvec< 4 >::strc _proxyv< 4, glm::vec4 >( const glm::vec4& v ) {
	prvec< 4 >::strc r;
	r.d[ 0 ] = v.x;
	r.d[ 1 ] = v.y;
	r.d[ 2 ] = v.z;
	r.d[ 3 ] = v.w;
	return r;
}

template<>
glm::vec2 _proxyv< 2, glm::vec2 >( const prvec< 2 >::strc& v ) {
	return glm::vec2( v.d[ 0 ], v.d[ 1 ] );
}

template<>
glm::vec3 _proxyv< 3, glm::vec3 >( const prvec< 3 >::strc& v ) {
	return glm::vec3( v.d[ 0 ], v.d[ 1 ], v.d[ 2 ] );
}

template<>
glm::vec4 _proxyv< 4, glm::vec4 >( const prvec< 4 >::strc& v ) {
	return glm::vec4( v.d[ 0 ], v.d[ 1 ], v.d[ 2 ], v.d[ 3 ] );
}

template< unsigned int i, unsigned int j, typename T >
typename prmat< i, j >::strc _proxym( const T& m );

template< unsigned int i, unsigned int j, typename T >
T _proxym( const typename prmat< i, j >::strc& m );

glm::quat _proxyq( const prvec< 4 >::strc& v ) {
	return glm::quat( v.d[ 3 ], v.d[ 0 ], v.d[ 1 ], v.d[ 2 ] );
}

prvec< 4 >::strc _proxyq( const glm::quat& q ) {
	prvec< 4 >::strc r;
	r.d[ 0 ] = q.x;
	r.d[ 1 ] = q.y;
	r.d[ 2 ] = q.z;
	r.d[ 3 ] = q.w;
	return r;
}

template<>
prmat< 4, 4 >::strc _proxym< 4, 4, glm::mat4 >( const glm::mat4& m ) {
	prmat< 4, 4 >::strc r;
	for( unsigned int i = 0; i < 4; ++i ) {
		r.d[ i ] = _proxyv< 4 >( m[ i ] );
	}
	return r;
}

template<>
glm::mat4 _proxym< 4, 4, glm::mat4 >( const prmat< 4, 4 >::strc& m ) {
	return glm::mat4(
		_proxyv< 4, glm::vec4 >( m.d[ 0 ] ),
		_proxyv< 4, glm::vec4 >( m.d[ 1 ] ),
		_proxyv< 4, glm::vec4 >( m.d[ 2 ] ),
		_proxyv< 4, glm::vec4 >( m.d[ 3 ] )
	);
}

prvec< 3 >::strc transform_get_local_position( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_local_position() );
}

void transform_set_local_position( long long h, prvec< 3 >::strc v ) {
	handle< scene_node_base::transform > hn(h);
	hn->set_local_position( _proxyv< 3, glm::vec3 >( v ) );
}

prvec< 4 >::strc transform_get_local_rotation( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyq( hn->get_local_rotation() );
}

void transform_set_local_rotation( long long h, prvec< 4 >::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_local_rotation( _proxyq( v ) );
}

prvec<3>::strc transform_get_local_scale( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_local_scale() );
}

void transform_set_local_scale( long long h, prvec<3>::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_local_scale( _proxyv< 3, glm::vec3 >( v ) );
}

prmat< 4, 4 >::strc transform_get_world_matrix( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxym< 4, 4 >( hn->get_world_matrix() );
}

prmat< 4, 4 >::strc transform_get_local_matrix( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxym< 4, 4 >( hn->get_local_matrix() );
}

prvec< 3 >::strc transform_get_position( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_position() );
}

void transform_set_position( long long h, prvec<3>::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_position( _proxyv< 3, glm::vec3 >( v ) );
}

prvec< 4 >::strc transform_get_rotation( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyq( hn->get_rotation() );
}

void transform_set_rotation( long long h, prvec<4>::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_rotation( glm::quat() );
}

prvec< 3 >::strc transform_get_scale( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_scale() );
}

void transform_set_scale( long long h, prvec< 3 >::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_local_scale( _proxyv< 3, glm::vec3 >( v ) );
}

prvec< 3 >::strc transform_get_local_euler_angles( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_local_euler_angles() );
}

void transform_set_local_euler_angles( long long h, prvec< 3 >::strc v ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_local_euler_angles( _proxyv< 3, glm::vec3 >( v ) );
}

bool transform_has_changed( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return hn->has_changed();
}

void transform_translate( long long h, prvec< 3 >::strc dir, int space ) {
	handle< scene_node_base::transform > hn( h );
	hn->translate( _proxyv< 3, glm::vec3 >( dir ), _trspace( space ) );
}

void transform_rotate_around( long long h, prvec< 3 >::strc cent, prvec< 3 >::strc axis, float angle, bool look ) {
	handle< scene_node_base::transform > hn( h );
	hn->rotate_around( _proxyv< 3, glm::vec3 >( cent ), _proxyv< 3, glm::vec3 >( axis ), angle, look );
}

void transform_rotate( long long h, prvec< 3 >::strc eul, int space ) {
	handle< scene_node_base::transform > hn( h );
	hn->rotate( _proxyv< 3, glm::vec3 >( eul ), _trspace( space ) );
}

void transform_look_at( long long h, long long at, prvec< 3 >::strc up ) {
	handle< scene_node_base::transform > hn( h );
	handle< scene_node_base::transform > hn2( at );
	hn->look_at( **hn2, _proxyv< 3, glm::vec3 >( up ) );
}

prvec< 3 >::strc transform_inverse_transform_position( long long h, prvec< 3 >::strc pos ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->inverse_transform_position( _proxyv< 3, glm::vec3 >( pos ) ) );
}

prvec< 3 >::strc transform_inverse_transform_direction( long long h, prvec< 3 >::strc dir ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->inverse_transform_direction( _proxyv< 3, glm::vec3 >( dir ) ) );
}

prvec< 3 >::strc transform_transform_position( long long h, prvec< 3 >::strc pos ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->transform_position( _proxyv< 3, glm::vec3 >( pos ) ) );
}

prvec<3>::strc transform_transform_direction( long long h, prvec<3>::strc dir ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->transform_direction( _proxyv< 3, glm::vec3 >( dir ) ) );
}

void transform_set_up( long long h, prvec<3>::strc up ) {
	handle< scene_node_base::transform > hn( h );
	hn->set_up( _proxyv< 3, glm::vec3 >( up ) );
}

prvec< 3 >::strc transform_get_up( long long h ) {
	handle< scene_node_base::transform > hn( h );
	return _proxyv< 3 >( hn->get_up() );
}
#pragma endregion



#include <core/scene_node.hpp>
const char* scene_node_get_class_string( long long h ) {
	const char* r = "";
	handle< i_scene_node > hn( h );
	di::component* cm = dynamic_cast< di::component* >( *hn );
	if( cm != nullptr ) {
		r = cm->get_meta_class().get_class_name().c_str();
	}
	return r;
}

long long scene_node_find( const char* name ) {
	static std::shared_ptr< scene_node_finder > finder = std::make_shared< scene_node_finder >();
	finder->set_name( name );
	auto ls = capi_bridge::instance->m_scene_manager->get_loaded();
	for( const auto& pp : ls ) {
		pp.second->traverse_depth( finder );
	}
	return reinterpret_cast< long long >( finder->get_result() );
}

long long scene_node_get_transform( long long h ) {
	handle< i_scene_node > hn( h );
	scene_node_base* sn = dynamic_cast< scene_node_base* >( *hn );
	return handle< scene_node_base::transform >::cast( &sn->get_transform() );
}

const char* scene_node_get_name( long long h ) {
	static std::string r;
	handle< i_scene_node > hn( h );
	r = hn->get_name();
	return r.c_str();
}

void scene_node_set_name( long long h, const char * name ) {
	handle< i_scene_node > hn( h );
	hn->set_name( name );
}

long long scene_node_get_parent( long long h ) {
	handle< i_scene_node > hn( h );
	return handle< i_scene_node >::cast( hn->get_parent() );
}

long long scene_node_get_children( long long h ) {
	return 0;
}

long long scene_node_get_root( long long h ) {
	handle< i_scene_node > hn( h );
	return handle< i_scene_node >::cast( hn->get_root() );
}

void scene_node_add_child( long long h, long long c ) {
	handle< i_scene_node > hn( h );
	handle< i_scene_node > hn2( c );
	hn->add_child( *hn2 );
}

void scene_node_remove_child( long long h, long long c ) {
	handle< i_scene_node > hn( h );
	handle< i_scene_node > hn2( c );
	hn->remove_child( *hn2 );
}

void scene_node_set_parent( long long h, long long p ) {
	handle< i_scene_node > hn( h );
	handle< i_scene_node > hn2( p );
	hn->remove_child( *hn2 );
}

void scene_node_traverse_depth( long long h, long long v ) {
	handle< i_scene_node > hn( h );
}

void scene_node_traverse_breadth( long long h, long long v ) {
	handle< i_scene_node > hn( h );
}

bool scene_node_is_root( long long h ) {
	handle< i_scene_node > hn( h );
	return hn->is_root();
}






void mesh_renderer_node_set_mesh( long long h, const char* mesh, bool async ) {
	handle< scene_node_base > mr( h );
	mr->set_attribute( "mesh_url", std::string( mesh ) );
	mr->reload( async );
}

const char* mesh_renderer_node_get_mesh( long long h ) {
	static std::string r;
	r = handle< scene_node_base >( h )->get_attribute( "mesh_url" );
	return r.c_str();
}





void application_open( void ) {
	
}

void application_exit( void ) {
	capi_bridge::instance->m_windowing->get_render_window()->close();
}

void application_load_scene( const char * name ) {
	capi_bridge::instance->m_scene_manager->load_scene( name, false );
}
