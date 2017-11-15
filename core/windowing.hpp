#pragma once
#include <string>
#include <vector>
#include <memory>
#include <thread>
struct ddvec2 {
	ddvec2( void ) = default;
	ddvec2( int x, int y )
		: x( x ), y( y ) {}
	int x { 0 };
	int y { 0 };
};

struct video_mode {
	video_mode( void ) = default;
	video_mode( int w, int h, int bpp, int rr )
		: width( w ),
		height( h ),
		bits_per_pixel( bpp ),
		refresh_rate( rr ) {}
	int width { 0 };
	int height { 0 };
	int bits_per_pixel { 0 };
	int refresh_rate { 0 };
};

class i_display_device {
public:
	virtual std::wstring get_name( void ) = 0;
	virtual ddvec2 get_position( void ) = 0;
	virtual ddvec2 get_physical_size( void ) = 0;
	virtual video_mode get_video_mode( void ) = 0;
	virtual std::vector< video_mode > get_video_modes( void ) = 0;
};

class i_render_window {
public:
	// Creates the window with the specified parameters
	virtual bool create( int width, int height, std::wstring const& caption, int flags ) = 0;
	virtual bool create_fullscreen( const std::wstring& caption, std::shared_ptr< i_display_device > display ) = 0;

	// Destroys the window
	virtual void destroy( void ) = 0;

	virtual bool has_focus( void ) const = 0;
	virtual void set_cursor_position( const ddvec2& pos ) = 0;
	virtual ddvec2 get_cursor_position( void ) = 0;
	virtual void show_cursor( void ) = 0;
	virtual void hide_cursor( void ) = 0;
	virtual bool cursor_shown( void ) = 0;

	// Iconifies or minimizes the window, causing it to only appear on the system tray
	virtual void minimize( void ) = 0;
	// Restores the previusly minimized window
	virtual void restore( void ) = 0;
	// Shows the window, making it appear on system tray, if it is hidden
	virtual void show( void ) = 0;
	// Hides the window from system tray if it is visible
	virtual void hide( void ) = 0;
	// Sets the text, presented on the window's top bar
	virtual void set_caption( const std::wstring& caption ) = 0;

	// Returns the position of the window in pixel coordinates
	// assuming 0;0 point at the top-left corner of the client display
	virtual ddvec2 get_position( void ) = 0;
	// Sets the position of the window in pixel coordinates
	// assuming 0;0 point at the top-left corner of the client display
	virtual void set_position( const ddvec2& position ) = 0;

	// Returns the size of the window
	virtual ddvec2 get_size( void ) = 0;
	// Sets the size of the window
	virtual void set_size( const ddvec2& size ) = 0;

	// Sets the window's associated clipboard buffer
	virtual void set_clipboard_string( const std::wstring& string ) = 0;
	// Reads the window's associated clipboard buffer
	virtual std::wstring get_clipboard_string( void ) = 0;

	virtual std::shared_ptr< i_display_device > get_display( void ) = 0;
	virtual bool is_open( void ) = 0;
	virtual void close( void ) = 0;
};

class i_graphics_context {
public:
	virtual bool create( i_render_window* target, i_graphics_context* share ) = 0;
	virtual void destroy( void ) = 0;
	virtual void swap_buffers( void ) = 0;
	virtual void clear_back_buffer( void ) = 0;
};

class i_context_guard {
public:
	virtual void make_current( i_graphics_context* c ) = 0;
	virtual i_graphics_context* get_current( void ) = 0;
	virtual bool is_current( i_graphics_context* c ) = 0;
	virtual void set_main_thread( void ) = 0;
	virtual std::thread::id get_main_thread( void ) const = 0;
	virtual bool is_main_thread( void ) = 0;
};

enum window_style {
	decorated_window = 0x1,
	popup_window = 0x2,
	sizeable_window = 0x4,
	hidden_window = 0x8,
	topmost_window = 0x10
};

namespace window_event {
	class i_keyboard_listener {
	public:
		virtual void respond( int key, bool pressed ) = 0;
	};

	class i_mouse_button_listener {
	public:
		virtual void respond( int key, bool pressed ) = 0;
	};

	class i_size_changed_listener {
	public:
		virtual void respond( int nx, int ny ) = 0;
	};

	class i_position_changed_listener {
	public:
		virtual void respond( int nx, int ny ) = 0;
	};

	class i_closed_listener {
	public:
		virtual void respond( void ) = 0;
	};

	class i_focus_changed_listener {
	public:
		virtual void respond( bool f ) = 0;
	};

	class i_minimized_listener {
	public:
		virtual void respond( bool m ) = 0;
	};

	class i_cursor_pass_listener {
	public:
		virtual void respond( bool c ) = 0;
	};

	class i_scroll_listener {
	public:
		virtual void respond( double s ) = 0;
	};

	class i_cursos_position_listener {
	public:
		virtual void respond( double x, double y ) = 0;
	};

	class i_drop_listener {
	public:
		virtual void respond( const std::vector< std::wstring >& ) = 0;
	};

	class i_char_listener {
	public:
		virtual void respond( char c ) = 0;
	};
}

class i_display_query {
public:
	virtual std::shared_ptr< i_display_device > get_primary_device( void ) = 0;
	virtual std::vector< std::shared_ptr< i_display_device > > get_devices( void ) = 0;
};

class i_input_manager {
public:
	virtual bool get_key_down( int key ) = 0;
	virtual bool get_key_up( int key ) = 0;
	virtual bool get_key( int key ) = 0;

	virtual bool get_mouse_down( int button ) = 0;
	virtual bool get_mouse_up( int button ) = 0;
	virtual bool get_mouse( int button ) = 0;

	virtual ddvec2 get_cursor_position( void ) = 0;
	virtual ddvec2 get_cursor_displacement( void ) = 0;

	virtual void update( void ) = 0;
	virtual i_render_window* get_window( void ) = 0;
};

class i_windowing_library {
public:
	virtual i_input_manager* get_input_manager( void ) = 0;
	virtual i_render_window* get_render_window( void ) = 0;
	virtual std::unique_ptr< i_graphics_context > new_gl_context( void ) = 0;
	virtual std::unique_ptr< i_graphics_context > new_d3d_context( void ) = 0;
	virtual i_context_guard* get_context_guard( void ) = 0;
	virtual std::unique_ptr< i_display_query > new_display_query( void ) = 0;
	virtual bool initialize( void ) = 0;
	virtual void poll_events( void ) = 0;
	virtual void terminate( void ) = 0;
};