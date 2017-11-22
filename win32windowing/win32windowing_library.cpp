#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/GL.h>
#include <di_rtlib/define_dependency.hpp>
#include <core/windowing.hpp>
#include <core/logger.hpp>
#include <iostream>
#define CLASS_NAME L"win32_eng_class"
class win32display_device
	: public i_display_device {

	std::wstring m_name;
public:
	win32display_device( const std::wstring& n )
		: m_name( n ) {}
private:
	DEVMODE _get_settings( void ) {
		DEVMODE r;
		ZeroMemory( &r, sizeof( DEVMODE ) );
		r.dmSize = sizeof( DEVMODE );
		EnumDisplaySettingsW( m_name.c_str(), ENUM_CURRENT_SETTINGS, &r );
		return r;
	}

	virtual std::wstring get_name( void ) override {
		return m_name;
	}

	virtual ddvec2 get_position( void ) override {
		const DEVMODE& m = _get_settings();
		return { m.dmPosition.x, m.dmPosition.y };
	}

	virtual ddvec2 get_physical_size( void ) override {
		const DEVMODE& m = _get_settings();
		return { static_cast< int >( m.dmPelsWidth ), static_cast< int >( m.dmPelsHeight ) };
	}

	virtual video_mode get_video_mode( void ) override {
		DEVMODE const& m = this->_get_settings();
		return {
			static_cast< int >( m.dmPelsWidth ),
			static_cast< int >( m.dmPelsHeight ),
			static_cast< int >( m.dmBitsPerPel ),
			static_cast< int >( m.dmDisplayFrequency )
		};
	}

	virtual std::vector< video_mode > get_video_modes( void ) override {
		DEVMODE m;
		ZeroMemory( &m, sizeof( DEVMODE ) );
		m.dmSize = sizeof( DEVMODE );
		std::vector< video_mode > result;
		for( DWORD index = 0; EnumDisplaySettingsW( this->get_name().c_str(), index, &m ); ++index ) {
			result.emplace_back( m.dmPelsWidth, m.dmPelsHeight, m.dmBitsPerPel, m.dmDisplayFrequency );
		}
		return move( result );
	}
};

class win32input_manager
	: public i_input_manager {
private:
	i_render_window* m_window;

	BYTE m_keyboard_state[ 256 ];
	BYTE m_pressed_keys[ 256 ];
	BYTE m_released_keys[ 256 ];

	bool m_button_state[ 6 ];
	bool m_pressed_buttons[ 6 ];
	bool m_released_buttons[ 6 ];

	POINT m_last_cursor_state;

public:
	win32input_manager( i_render_window* wnd )
		: m_window( wnd ) { }

private:
	virtual bool get_key_down( int key ) override {
		return ( m_pressed_keys[ key ] & 0x80 ) != 0;
	}

	virtual bool get_key_up( int key ) override {
		return ( m_released_keys[ key ] & 0x80 ) != 0;
	}

	virtual bool get_key( int key ) override {
		return ( m_keyboard_state[ key ] & 0x80 ) != 0;
	}

	virtual bool get_mouse_down( int button ) override {
		return m_pressed_buttons[ button ];
	}

	virtual bool get_mouse_up( int button ) override {
		return m_released_buttons[ button ];
	}

	virtual bool get_mouse( int button ) override {
		return m_button_state[ button ];
	}

	virtual ddvec2 get_cursor_position( void ) override {
		return { m_last_cursor_state.x, m_last_cursor_state.y };
	}

	virtual ddvec2 get_cursor_displacement( void ) override {
		POINT current_state;
		GetCursorPos( &current_state );
		return { m_last_cursor_state.x - current_state.x, m_last_cursor_state.y - current_state.y };
	}

	virtual void update( void ) override {
		static BYTE tmp[ 256 ];
		ZeroMemory( tmp, 256 );
		ZeroMemory( m_pressed_keys, 256 );
		ZeroMemory( m_released_keys, 256 );

		static bool btn_tmp[ 6 ];
		ZeroMemory( btn_tmp, 6 );
		ZeroMemory( m_pressed_buttons, 6 );
		ZeroMemory( m_released_buttons, 6 );

		if( !this->get_window()->has_focus() ) {
			return;
		}

		for( size_t i = 0; i < 256; ++i ) {
			tmp[ i ] |= m_keyboard_state[ i ];
		}

		if( GetKeyboardState( m_keyboard_state ) == FALSE ) return;

		for( size_t i = 0; i < 256; ++i ) {
			if( tmp[ i ] > m_keyboard_state[ i ] ) {
				m_released_keys[ i ] |= tmp[ i ];
			} else {
				if( tmp[ i ] < m_keyboard_state[ i ] ) {
					m_pressed_keys[ i ] |= m_keyboard_state[ i ];
				}
			}
		}

		for( size_t i = 0; i < 6; ++i ) {
			btn_tmp[ i ] = m_button_state[ i ];
		}

		m_button_state[ VK_LBUTTON ] = ( GetKeyState( VK_LBUTTON ) & 0x8000 ) != 0;
		m_button_state[ VK_RBUTTON ] = ( GetKeyState( VK_RBUTTON ) & 0x8000 ) != 0;
		m_button_state[ VK_MBUTTON ] = ( GetKeyState( VK_MBUTTON ) & 0x8000 ) != 0;
		m_button_state[ VK_XBUTTON1 ] = ( GetKeyState( VK_XBUTTON1 ) & 0x8000 ) != 0;
		m_button_state[ VK_XBUTTON2 ] = ( GetKeyState( VK_XBUTTON2 ) & 0x8000 ) != 0;

		for( size_t i = 0; i < 6; ++i ) {
			m_released_buttons[ i ] = btn_tmp[ i ] && !m_button_state[ i ];
			m_pressed_buttons[ i ] = !btn_tmp[ i ] && m_button_state[ i ];
		}

		GetCursorPos( &m_last_cursor_state );
	}

	virtual i_render_window* get_window( void ) override {
		return m_window;
	}
};

class win32render_window
	: public i_render_window {
private:
	i_logger* m_logger;

public:
	HWND m_handle;

	win32render_window( i_logger* l )
		: m_logger( l ) {}

private:
	std::shared_ptr< i_display_device > m_display;
	bool m_open { true };

	friend LRESULT CALLBACK _wnd_proc( HWND handle, UINT msg, WPARAM w_param, LPARAM l_param ) {
		win32render_window* wnd = reinterpret_cast< win32render_window* >( GetWindowLongPtrW( handle, 0 ) );

		switch( msg ) {
		case WM_NCCREATE:
		{
			CREATESTRUCTW* create_struct = reinterpret_cast< CREATESTRUCTW* >( l_param );
			SetWindowLongPtr( handle, 0, reinterpret_cast< LONG_PTR >( create_struct->lpCreateParams ) );
			break;
		}

		case WM_CLOSE:
		{
			//wnd->_raise_closed();
			wnd->close();
			return 0;
		}
		case WM_DESTROY:
		case WM_NCDESTROY:
		{
			wnd->close();
			return 0;
		}

		case WM_SETFOCUS:
		{
//			wnd->_raise_focus_changed( true );
			return 0;
		}

		case WM_KILLFOCUS:
		{
//			wnd->_raise_focus_changed( false );
			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch( w_param & 0xfff0 ) {
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
			{
				if( wnd->get_display() != nullptr ) {
					return 0;
				} else {
					break;
				}
			}
			case SC_KEYMENU:
				return 0;
			}
			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
//			wnd->_raise_keyboard( w_param, true );
			break;
		}

		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
//			wnd->_raise_keyboard( w_param, false );
			break;
		}

		case WM_CHAR:
		{
//			wnd->_raise_char( static_cast< char >( w_param ) );
			return 0;
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		{
			SetCapture( handle );
//			wnd->_raise_mouse_button( w_param, true );
			return 0;
		}

		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		{
			ReleaseCapture();
//			wnd->_raise_mouse_button( w_param, false );
			return 0;
		}

		case WM_ERASEBKGND:
		{
			return TRUE;
		}
		}
		return DefWindowProc( handle, msg, w_param, l_param );
	}

	// Creates the window with the specified parameters
	virtual bool create( int width, int height, std::wstring const& caption, int flags ) override {
		RECT r {
			( GetSystemMetrics( SM_CXSCREEN ) - width ) / 2,
			( GetSystemMetrics( SM_CYSCREEN ) - height ) / 2,
			width,
			height
		};

		DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		DWORD estyle = WS_EX_APPWINDOW;

		if( ( flags & window_style::hidden_window ) == 0 ) {
			style |= WS_VISIBLE;
		}

		if( ( flags & window_style::decorated_window ) != 0 ) {
			style |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		}

		if( ( flags & window_style::popup_window ) != 0 ) {
			style |= WS_POPUP;
		}

		if( ( flags & window_style::sizeable_window ) != 0 ) {
			style |= WS_MAXIMIZEBOX | WS_SIZEBOX;
			estyle |= WS_EX_WINDOWEDGE;
		}

		if( ( flags & window_style::topmost_window ) != 0 ) {
			estyle |= WS_EX_TOPMOST;
		}

		AdjustWindowRectEx( &r, style, FALSE, estyle );
		m_handle = CreateWindowEx( estyle, CLASS_NAME, caption.c_str(), style,
			CW_USEDEFAULT, CW_USEDEFAULT, r.right, r.bottom, NULL, NULL, GetModuleHandle( NULL ), this );
		if( m_handle == NULL ) {
			return false;
		}
		return true;
	}

	virtual bool create_fullscreen( const std::wstring& caption, std::shared_ptr< i_display_device > display ) override {
		const ddvec2& p = display->get_position();
		const ddvec2& s = display->get_physical_size();
		m_handle = CreateWindowEx( WS_EX_APPWINDOW, CLASS_NAME, caption.c_str(),
			WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, p.x, p.y, s.x, s.y, NULL, NULL, GetModuleHandle( NULL ), this );
		if( !m_handle ) {
			// logerror
			return false;
		}
		m_display = display;
		return true;
	}

	// Destroys the window
	virtual void destroy( void ) override {
		DestroyWindow( m_handle );
	}

	virtual bool has_focus( void ) const override {
		return GetActiveWindow() == m_handle;
	}

	virtual void set_cursor_position( const ddvec2& pos ) override {
		SetCursorPos( pos.x, pos.y );
	}

	virtual ddvec2 get_cursor_position( void ) override {
		POINT p;
		GetCursorPos( &p );
		return { p.x, p.y };
	}

	virtual void show_cursor( void ) override {
		ShowCursor( true );
	}

	virtual void hide_cursor( void ) override {
		ShowCursor( false );
	}

	virtual bool cursor_shown( void ) override {
		CURSORINFO c;
		c.cbSize = sizeof( CURSORINFO );
		GetCursorInfo( &c );
		return ( c.flags & CURSOR_SHOWING ) != 0;
	}

	// Iconifies or minimizes the window, causing it to only appear on the system tray
	virtual void minimize( void ) override {
		ShowWindow( m_handle, SW_MINIMIZE );
	}

	// Restores the previusly minimized window
	virtual void restore( void ) override {
		ShowWindow( m_handle, SW_RESTORE );
	}

	// Shows the window, making it appear on system tray, if it is hidden
	virtual void show( void ) override {
		ShowWindow( m_handle, SW_SHOW );
	}

	// Hides the window from system tray if it is visible
	virtual void hide( void ) override {
		ShowWindow( m_handle, SW_HIDE );
	}

	// Sets the text, presented on the window's top bar
	virtual void set_caption( const std::wstring& caption ) override {
		SetWindowTextW( m_handle, caption.c_str() );
	}

	// Returns the position of the window in pixel coordinates
	// assuming 0;0 point at the top-left corner of the client display
	virtual ddvec2 get_position( void ) override {
		RECT r;
		ZeroMemory( &r, sizeof( RECT ) );
		GetWindowRect( m_handle, &r );
		return { r.left, r.top };
	}

	// Sets the position of the window in pixel coordinates
	// assuming 0;0 point at the top-left corner of the client display
	virtual void set_position( const ddvec2& position ) override {
		SetWindowPos( m_handle, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER );
	}

	// Returns the size of the window
	virtual ddvec2 get_size( void ) override {
		RECT r;
		ZeroMemory( &r, sizeof( RECT ) );
		GetWindowRect( m_handle, &r );
		return { r.right - r.left, r.bottom - r.top };
	}

	// Sets the size of the window
	virtual void set_size( const ddvec2& size ) override {
		SetWindowPos( m_handle, NULL, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER );
	}

	// Sets the window's associated clipboard buffer
	virtual void set_clipboard_string( const std::wstring& string ) override {
		OpenClipboard( m_handle );
		EmptyClipboard();
		HGLOBAL cb_handle = GlobalAlloc( GMEM_MOVEABLE, string.length() * sizeof( TCHAR ) );
		memcpy( static_cast< LPTSTR >( GlobalLock( cb_handle ) ), &string [ 0 ], string.length() );
		GlobalUnlock( cb_handle );
		SetClipboardData( CF_TEXT, cb_handle );
		CloseClipboard();
	}

	// Reads the window's associated clipboard buffer
	virtual std::wstring get_clipboard_string( void ) override {
		OpenClipboard( m_handle );
		HGLOBAL cb_handle = GetClipboardData( CF_TEXT );
		LPTSTR lpstr = static_cast< LPTSTR >( GlobalLock( cb_handle ) );
		std::wstring result( lstrlenW( lpstr ), '\0' );
		memcpy( &result [ 0 ], lpstr, result.size() );
		GlobalUnlock( cb_handle );
		CloseClipboard();
		return move( result );
	}

	virtual std::shared_ptr< i_display_device > get_display( void ) override {
		std::shared_ptr< i_display_device > r = m_display;
		if( !r ) {
			MONITORINFOEX mi;
			ZeroMemory( &mi, sizeof( MONITORINFOEX ) );
			mi.cbSize = sizeof( MONITORINFOEX );
			GetMonitorInfo( MonitorFromWindow( m_handle, MONITOR_DEFAULTTONEAREST ), &mi );
			r = std::make_shared< win32display_device >( mi.szDevice );
		}
		return r;
	}

	virtual bool is_open( void ) override {
		return m_open;
	}

	virtual void close( void ) override {
		m_open = false;
	}
};

class win32gl_context
	: public i_graphics_context, public di::component {
private:
	component_dependency( m_logger, i_logger );

	int m_target_width { 0 };
	int m_target_height { 0 };
	
public:
	HDC m_hdc;
	HGLRC m_glhdc;

	~win32gl_context( void ) {
		this->destroy();
	}

private:
	friend void APIENTRY context_callback( GLenum s, GLenum t, GLuint, GLenum sev,
		GLsizei, const GLchar* m, const GLvoid* param ) {
		char* str_source = "0";
		char* str_type = str_source;
		char* str_severity = str_source;

		switch( s ) {
		case GL_DEBUG_SOURCE_API_ARB:
			str_source = "API";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
			str_source = "WINDOWS";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
			str_source = "SHADER COMP.";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
			str_source = "3RD PARTY";
			break;
		case GL_DEBUG_SOURCE_APPLICATION_ARB:
			str_source = "APP";
			break;
		case GL_DEBUG_SOURCE_OTHER_ARB:
			str_source = "OTHER";
			break;
		}
		switch( t ) {
		case GL_DEBUG_TYPE_ERROR_ARB:
			str_type = "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
			str_type = "Deprecated";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
			str_type = "Undefined";
			break;
		case GL_DEBUG_TYPE_PORTABILITY_ARB:
			str_type = "Portability";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE_ARB:
			str_type = "Performance";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			str_type = "Other";
			break;
		}
		switch( sev ) {
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			str_severity = "High";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			str_severity = "Medium";
			break;
		case GL_DEBUG_SEVERITY_LOW_ARB:
			str_severity = "Low";
			break;
		}

		static_cast< const i_logger* >( param )->init_stream( priority::debug, "win32gl_context" ) 
			<< "gl context: " << str_severity << " - " << str_source << " - " << str_type << " - " << m;
	}

	void _set_pixelformat( HDC context, const PIXELFORMATDESCRIPTOR& fallback ) {
		int format_index = 0;
		if( wglChoosePixelFormatARB ) {
			
			int pattribs [] = {
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				WGL_RED_BITS_ARB, 8,
				WGL_GREEN_BITS_ARB, 8,
				WGL_BLUE_BITS_ARB, 8,
				WGL_ALPHA_BITS_ARB, 8,
				0
			};

			UINT n_formats = 0;
			if( !wglChoosePixelFormatARB( context, pattribs, nullptr, 1, &format_index, &n_formats ) ) {
				format_index = ChoosePixelFormat( context, &fallback );
			}
		} else {
			format_index = ChoosePixelFormat( context, &fallback );
		}
		SetPixelFormat( context, format_index, &fallback );
	}

	bool _load_extensions( HDC tctx, HGLRC glctx ) {
		bool r = false;
		glewExperimental = GL_TRUE;
		if( wglMakeCurrent( tctx, glctx ) == TRUE ) {
			if( glewInit() == GLEW_OK ) {
				r = true;
			} else {
				error( "failed to initialize glew on new context" );
			}
		}
		
#ifdef _DEBUG
		glDebugMessageCallbackARB( context_callback, m_logger.get() );
		//glDebugMessageControlARB( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH_ARB, 0, NULL, GL_TRUE );
#endif
		wglMakeCurrent( tctx, NULL );
		return r;
	}

	HGLRC _create_gl_context( HDC tctx, HGLRC share ) {
		HGLRC r = NULL;
		if( wglCreateContextAttribsARB ) {
			int cattribs [] = {
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#ifdef _DEBUG
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif // ~_DEBUG
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,
				0
			};

			r = wglCreateContextAttribsARB( tctx, share, cattribs );
		} else {
			r = wglCreateContext( tctx );
		}
		
		if( share != 0 && wglShareLists( r, share ) == FALSE ) {
			LPSTR err_msg = nullptr;
			size_t s = FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), static_cast< LPSTR >( err_msg ), 0, NULL );

			serror << "context sharing was requested, but failed to set up:\n\t" << std::string( err_msg, s );
			LocalFree( err_msg );
		}
		return r;
	}

	virtual bool create( i_render_window* target, i_graphics_context* share ) override {
		bool r = false;

		m_hdc = GetDC( dynamic_cast< win32render_window* >( target )->m_handle );
		m_target_width = target->get_size().x;
		m_target_height = target->get_size().y;

		if( share == nullptr ) {
			PIXELFORMATDESCRIPTOR false_desc = {
				sizeof( PIXELFORMATDESCRIPTOR ),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,           
				32,                       
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                       
				8,                       
				0,                      
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};

			HDC desktop_context = GetDC( GetDesktopWindow() );
			SetPixelFormat( desktop_context, ChoosePixelFormat( desktop_context, &false_desc ), &false_desc );
			HGLRC false_context = wglCreateContext( desktop_context );

			if( false_context != NULL ) {
				_load_extensions( desktop_context, false_context );

				if( glewIsExtensionSupported("wglEnumGpusNv") ) {
					sinfo << "gpu enumeration is available, select device:";

					HGPUNV gpuhnd;
					std::vector<GPU_DEVICE> devices;
					for( uint8_t i = 0; wglEnumGpusNV( i, &gpuhnd ); ++i ) {
						devices.emplace_back();
						devices.back().cb = sizeof( GPU_DEVICE );
						wglEnumGpuDevicesNV( gpuhnd, i, &devices.back() );

						sinfo << "device id: " << i << " name: " << devices.back().DeviceName << " description: " << devices.back().DeviceString;
					}

					uint8_t selected = 0;
					bool invalid = true;

					while( invalid ) {
						sinfo << "enter valid device id:";
						std::cin >> selected;

						invalid = selected >= devices.size();
					}

					sinfo << "selected device: " << selected;

				} else {
					sinfo << "gpu enumeration is not available";
				}



				_set_pixelformat( m_hdc, false_desc );
				m_glhdc = _create_gl_context( m_hdc, NULL );
				r = m_glhdc != NULL && _load_extensions( m_hdc, m_glhdc );
				wglDeleteContext( false_context );
			}
		} else {
			HGLRC shared_context = NULL;
			if( typeid( *share ) == typeid( win32gl_context ) ) {
				shared_context = static_cast< win32gl_context* >( share )->m_glhdc;
			}
			m_glhdc = _create_gl_context( m_hdc, shared_context );
			r = m_glhdc != NULL;
		}

		return r;
	}

	virtual void destroy( void ) override {
		wglMakeCurrent( m_hdc, NULL );
		wglDeleteContext( m_glhdc );
	}

	virtual void swap_buffers( void ) override {
		SwapBuffers( m_hdc );
	}

	virtual void clear_back_buffer( void ) override {
		glViewport( 0, 0, m_target_width, m_target_height );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}
};

class win32d3d_context 
	: public i_graphics_context, public di::component {
private:
	component_dependency( m_logger, i_logger );

	virtual bool create( i_render_window* target, i_graphics_context* share ) override {
		return true;
	}

	virtual void destroy( void ) override {

	}

	virtual void swap_buffers( void ) override {

	}

	virtual void clear_back_buffer( void ) override { }
};

#include <thread>
#include <unordered_map>
class win32context_guard
	: public i_context_guard {
private:
	i_logger* m_logger;

	std::thread::id m_main;
	std::unordered_map< std::thread::id, i_graphics_context* > m_contexts;

public:
	win32context_guard( i_logger* l )
		: m_logger( l ) {}
private:
	virtual void make_current( i_graphics_context* c ) override {
		if( typeid( *c ) == typeid( win32d3d_context ) ) {

		} else if( typeid( *c ) == typeid( win32gl_context ) ) {
			win32gl_context* glctx = static_cast< win32gl_context* >( c );
			if( wglMakeCurrent( glctx->m_hdc, glctx->m_glhdc ) ) {
				m_contexts[ std::this_thread::get_id() ] = c;
			} else {
				error( "failed to make current the requested context" );
			}
		} else {
			error( "unrecognized context type, supported types are win32d3d_context and win32gl_context" );
		}
	}

	virtual i_graphics_context* get_current( void ) override {
		i_graphics_context* r = nullptr;
		auto fit = m_contexts.find( std::this_thread::get_id() );
		if( fit != m_contexts.end() ) {
			r = fit->second;
		}
		return r;
	}

	virtual bool is_current( i_graphics_context* c ) override {
		auto fit = m_contexts.find( std::this_thread::get_id() );
		return fit != m_contexts.end() && fit->second == c;
	}

	virtual void set_main_thread( void ) override {
		m_main = std::this_thread::get_id();
	}

	virtual std::thread::id get_main_thread( void ) const {
		return m_main;
	}

	virtual bool is_main_thread( void ) {
		return m_main == std::this_thread::get_id();
	}
};

class win32display_query
	: public i_display_query {

	virtual std::shared_ptr< i_display_device > get_primary_device( void ) override {
		DISPLAY_DEVICE device;
		ZeroMemory( &device, sizeof( DISPLAY_DEVICE ) );
		device.cb = sizeof( DISPLAY_DEVICE );
		for( DWORD index = 0; EnumDisplayDevicesW( NULL, index, &device, 0 ); ++index ) {
			if( device.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE ) {
				break;
			}
		}
		return std::make_shared< win32display_device >( device.DeviceName );
	}

	virtual std::vector< std::shared_ptr< i_display_device > > get_devices( void ) override {
		DISPLAY_DEVICE device;
		ZeroMemory( &device, sizeof( DISPLAY_DEVICE ) );
		device.cb = sizeof( DISPLAY_DEVICE );
		std::vector< std::shared_ptr< i_display_device > > result;
		for( DWORD index = 0; EnumDisplayDevicesW( NULL, index, &device, 0 ); ++index ) {
			result.emplace_back( new win32display_device( device.DeviceName ) );
		}
		return move( result );
	}
};

class win32windowing_library
	: public i_windowing_library, public di::component {
private:
	component_dependency( m_logger, i_logger );
	std::unique_ptr< i_render_window > m_window;
	std::unique_ptr< i_input_manager > m_input;

	static std::unique_ptr< i_context_guard > context_guard;

	virtual i_input_manager* get_input_manager( void ) override {
		if( !m_input ) {
			m_input = std::make_unique< win32input_manager >( m_window.get() );
		}
		return m_input.get();
	}

	virtual i_render_window* get_render_window( void ) override {
		if( !m_window ) {
			m_window = std::make_unique< win32render_window >( m_logger );
		}
		return m_window.get();
	}

	virtual std::unique_ptr< i_graphics_context > new_gl_context( void ) override {
		return std::make_unique< win32gl_context >();
	}

	virtual std::unique_ptr< i_graphics_context > new_d3d_context( void ) override {
		return std::make_unique< win32d3d_context >();
	}

	virtual i_context_guard* get_context_guard( void ) override {
		if( !context_guard ) {
			context_guard = std::make_unique< win32context_guard >( m_logger );
		}
		return context_guard.get();
	}

	virtual std::unique_ptr< i_display_query > new_display_query( void ) override {
		return std::make_unique< win32display_query >();
	}

	virtual bool initialize( void ) override {
		WNDCLASS c;
		ZeroMemory( &c, sizeof( WNDCLASSW ) );
		c.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		c.lpfnWndProc = _wnd_proc;
		c.cbWndExtra = sizeof( void* ) + sizeof( int );
		c.hInstance = GetModuleHandle( NULL );
		c.hCursor = LoadCursor( NULL, IDC_ARROW );
		c.lpszClassName = CLASS_NAME;
		c.hIcon = LoadIconA( GetModuleHandle( NULL ), "PAR_ICO" );

		if( !c.hIcon ) {
			c.hIcon = LoadIconW( NULL, IDI_WINLOGO );
		}

		if( !RegisterClass( &c ) ) {
			error( "failed to register window class" );
			return false;
		}

		return true;
	}

	virtual void poll_events( void ) override {
		static MSG m;
		while( PeekMessage( &m, NULL, 0, 0, PM_REMOVE ) != FALSE ) {
			TranslateMessage( &m );
			DispatchMessage( &m );
		}
	}

	virtual void terminate( void ) override {
		UnregisterClass( CLASS_NAME, GetModuleHandle( NULL ) );
	}
};

std::unique_ptr< i_context_guard > win32windowing_library::context_guard;

#include "../di_rtlib/register_class.hpp"
register_class( win32windowing_library );
register_class( win32gl_context );
register_class( win32d3d_context );