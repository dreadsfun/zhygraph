#pragma once
#include "export.h"

#pragma region proxies
template< unsigned int c >
struct prvec {
	typedef struct {
		float d[ c ];
	} strc;
};

template< unsigned int row, unsigned int col >
struct prmat {
	typedef struct {
		typename prvec< row >::strc d[ col ];
	} strc;
};
#pragma endregion

extern "C" {
#pragma region common
	
#pragma endregion

#pragma region input
#  pragma region keys
	extern CAPI_SHARED int keys_backspace;
	extern CAPI_SHARED int keys_tab;
	extern CAPI_SHARED int keys_clear;
	extern CAPI_SHARED int keys_return;
	extern CAPI_SHARED int keys_shift;
	extern CAPI_SHARED int keys_control;
	extern CAPI_SHARED int keys_alt;
	extern CAPI_SHARED int keys_pause;
	extern CAPI_SHARED int keys_capital;
	extern CAPI_SHARED int keys_escape;
	extern CAPI_SHARED int keys_space;
	extern CAPI_SHARED int keys_prior;
	extern CAPI_SHARED int keys_next;
	extern CAPI_SHARED int keys_end;
	extern CAPI_SHARED int keys_home;
	extern CAPI_SHARED int keys_left;
	extern CAPI_SHARED int keys_up;
	extern CAPI_SHARED int keys_right;
	extern CAPI_SHARED int keys_down;
	extern CAPI_SHARED int keys_select;
	extern CAPI_SHARED int keys_print;
	extern CAPI_SHARED int keys_execute;
	extern CAPI_SHARED int keys_snapshot;
	extern CAPI_SHARED int keys_insert;
	extern CAPI_SHARED int keys_delete;
	extern CAPI_SHARED int keys_help;

	extern CAPI_SHARED int keys_leftwin;
	extern CAPI_SHARED int keys_rightwin;
	extern CAPI_SHARED int keys_apps;
	extern CAPI_SHARED int keys_sleep;

	extern CAPI_SHARED int keys_numpad0;
	extern CAPI_SHARED int keys_numpad1;
	extern CAPI_SHARED int keys_numpad2;
	extern CAPI_SHARED int keys_numpad3;
	extern CAPI_SHARED int keys_numpad4;
	extern CAPI_SHARED int keys_numpad5;
	extern CAPI_SHARED int keys_numpad6;
	extern CAPI_SHARED int keys_numpad7;
	extern CAPI_SHARED int keys_numpad8;
	extern CAPI_SHARED int keys_numpad9;

	extern CAPI_SHARED int keys_multiply;
	extern CAPI_SHARED int keys_add;
	extern CAPI_SHARED int keys_separator;
	extern CAPI_SHARED int keys_subtract;
	extern CAPI_SHARED int keys_decimal;
	extern CAPI_SHARED int keys_divide;

	extern CAPI_SHARED int keys_f1;
	extern CAPI_SHARED int keys_f2;
	extern CAPI_SHARED int keys_f3;
	extern CAPI_SHARED int keys_f4;
	extern CAPI_SHARED int keys_f5;
	extern CAPI_SHARED int keys_f6;
	extern CAPI_SHARED int keys_f7;
	extern CAPI_SHARED int keys_f8;
	extern CAPI_SHARED int keys_f9;
	extern CAPI_SHARED int keys_f10;
	extern CAPI_SHARED int keys_f11;
	extern CAPI_SHARED int keys_f12;
	extern CAPI_SHARED int keys_f13;
	extern CAPI_SHARED int keys_f14;
	extern CAPI_SHARED int keys_f15;

	extern CAPI_SHARED int keys_numlock;
	extern CAPI_SHARED int keys_scroll;

	extern CAPI_SHARED int keys_leftshift;
	extern CAPI_SHARED int keys_rightshift;
	extern CAPI_SHARED int keys_leftcontrol;
	extern CAPI_SHARED int keys_rightcontrol;
	extern CAPI_SHARED int keys_leftmenu;
	extern CAPI_SHARED int keys_rightmenu;

	extern CAPI_SHARED int keys_volmute;
	extern CAPI_SHARED int keys_voldown;
	extern CAPI_SHARED int keys_volup;

	extern CAPI_SHARED int keys_0;
	extern CAPI_SHARED int keys_1;
	extern CAPI_SHARED int keys_2;
	extern CAPI_SHARED int keys_3;
	extern CAPI_SHARED int keys_4;
	extern CAPI_SHARED int keys_5;
	extern CAPI_SHARED int keys_6;
	extern CAPI_SHARED int keys_7;
	extern CAPI_SHARED int keys_8;
	extern CAPI_SHARED int keys_9;

	extern CAPI_SHARED int keys_a;
	extern CAPI_SHARED int keys_b;
	extern CAPI_SHARED int keys_c;
	extern CAPI_SHARED int keys_d;
	extern CAPI_SHARED int keys_e;
	extern CAPI_SHARED int keys_f;
	extern CAPI_SHARED int keys_g;
	extern CAPI_SHARED int keys_h;
	extern CAPI_SHARED int keys_i;
	extern CAPI_SHARED int keys_j;
	extern CAPI_SHARED int keys_k;
	extern CAPI_SHARED int keys_l;
	extern CAPI_SHARED int keys_m;
	extern CAPI_SHARED int keys_n;
	extern CAPI_SHARED int keys_o;
	extern CAPI_SHARED int keys_p;
	extern CAPI_SHARED int keys_q;
	extern CAPI_SHARED int keys_r;
	extern CAPI_SHARED int keys_s;
	extern CAPI_SHARED int keys_t;
	extern CAPI_SHARED int keys_u;
	extern CAPI_SHARED int keys_v;
	extern CAPI_SHARED int keys_w;
	extern CAPI_SHARED int keys_x;
	extern CAPI_SHARED int keys_y;
	extern CAPI_SHARED int keys_z;
#  pragma endregion

#  pragma region buttons
	extern CAPI_SHARED int buttons_left;
	extern CAPI_SHARED int buttons_right;
	extern CAPI_SHARED int buttons_middle;
	extern CAPI_SHARED int buttons_extra1;
	extern CAPI_SHARED int buttons_extra2;
#  pragma endregion

#  pragma region input classssssss
	CAPI_SHARED bool input_get_key_down( int key );
	CAPI_SHARED bool input_get_key_up( int key );
	CAPI_SHARED bool input_get_key( int key );

	CAPI_SHARED bool input_get_button_down( int key );
	CAPI_SHARED bool input_get_button_up( int key );
	CAPI_SHARED bool input_get_button( int key );

	CAPI_SHARED prvec< 2 >::strc input_get_cursor_position( void );
	CAPI_SHARED prvec< 2 >::strc input_get_cursor_displacement( void );
#  pragma endregion
#pragma endregion

#pragma region log class
	CAPI_SHARED void log_debug( const char* msg );
	CAPI_SHARED void log_info( const char* msg );
	CAPI_SHARED void log_warn( const char* msg );
	CAPI_SHARED void log_error( const char* msg );
#pragma endregion

#pragma region transform class
	CAPI_SHARED prvec< 3 >::strc transform_get_local_position( long long h );
	CAPI_SHARED void transform_set_local_position( long long h, prvec< 3 >::strc v );
	CAPI_SHARED prvec< 4 >::strc transform_get_local_rotation( long long h );
	CAPI_SHARED void transform_set_local_rotation( long long h, prvec< 4 >::strc v );
	CAPI_SHARED prvec< 3 >::strc transform_get_local_scale( long long h );
	CAPI_SHARED void transform_set_local_scale( long long h, prvec< 3 >::strc v );
	CAPI_SHARED prmat< 4, 4 >::strc transform_get_world_matrix( long long h );
	CAPI_SHARED prmat< 4, 4 >::strc transform_get_local_matrix( long long h );
	CAPI_SHARED prvec< 3 > ::strc transform_get_position( long long h );
	CAPI_SHARED void transform_set_position( long long h, prvec< 3 >::strc v );
	CAPI_SHARED prvec< 4 >::strc transform_get_rotation( long long h );
	CAPI_SHARED void transform_set_rotation( long long h, prvec< 4 >::strc v );
	CAPI_SHARED prvec< 3 >::strc transform_get_scale( long long h );
	CAPI_SHARED void transform_set_scale( long long h, prvec< 3 >::strc v );
	CAPI_SHARED prvec< 3 >::strc transform_get_local_euler_angles( long long h );
	CAPI_SHARED void transform_set_local_euler_angles( long long h, prvec< 3 >::strc v );
	CAPI_SHARED bool transform_has_changed( long long h );
	CAPI_SHARED void transform_translate( long long h, prvec< 3 >::strc dir, int space );
	CAPI_SHARED void transform_rotate_around( long long h, prvec< 3 >::strc cent, prvec< 3 >::strc axis, float angle, bool look );
	CAPI_SHARED void transform_rotate( long long h, prvec< 3 >::strc eul, int space );
	CAPI_SHARED void transform_look_at( long long h, long long at, prvec< 3 >::strc up );
	CAPI_SHARED prvec< 3 >::strc transform_inverse_transform_position( long long h, prvec< 3 >::strc pos );
	CAPI_SHARED prvec< 3 >::strc transform_inverse_transform_direction( long long h, prvec< 3 >::strc dir );
	CAPI_SHARED prvec< 3 >::strc transform_transform_position( long long h, prvec< 3 >::strc pos );
	CAPI_SHARED prvec< 3 >::strc transform_transform_direction( long long h, prvec< 3 >::strc dir );
	CAPI_SHARED void transform_set_up( long long h, prvec< 3 >::strc up );
	CAPI_SHARED prvec< 3 >::strc transform_get_up( long long h );
#pragma endregion

#pragma region scene_node class
	//CAPI_SHARED long long scene_node_create( const char* name, long long parent );
	CAPI_SHARED const char* scene_node_get_class_string( long long h );
	CAPI_SHARED long long scene_node_find( const char* name );
	CAPI_SHARED long long scene_node_get_transform( long long h );
	CAPI_SHARED const char* scene_node_get_name( long long h );
	CAPI_SHARED void scene_node_set_name( long long h, const char* name );
	CAPI_SHARED long long scene_node_get_parent( long long h );
	CAPI_SHARED long long scene_node_get_children( long long h );
	CAPI_SHARED long long scene_node_get_root( long long h );
	CAPI_SHARED void scene_node_add_child( long long h, long long c );
	CAPI_SHARED void scene_node_remove_child( long long h, long long c );
	CAPI_SHARED void scene_node_set_parent( long long h, long long p );
	CAPI_SHARED void scene_node_traverse_depth( long long h, long long v );
	CAPI_SHARED void scene_node_traverse_breadth( long long h, long long v );
	CAPI_SHARED bool scene_node_is_root( long long h );
#pragma endregion

#pragma region mesh_renderer_node class
	CAPI_SHARED void mesh_renderer_node_set_mesh( long long h, const char* mesh, bool async );
	CAPI_SHARED const char* mesh_renderer_node_get_mesh( long long h );
#pragma endregion

#pragma region application class
	CAPI_SHARED void application_open( void );
	CAPI_SHARED void application_exit( void );
	CAPI_SHARED void application_load_scene( const char* name );
#pragma endregion
}