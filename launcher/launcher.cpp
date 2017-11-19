#include <string>
#include <fstream>
#include <thread>
#include <core/time.hpp>
#include <core/graphics.hpp>
#include <core/logger.hpp>
#include <core/scene.hpp>
#include <core/windowing.hpp>
#include <core/scripting.hpp>
#include <di_rtlib/define_attribute.hpp>
#include <di_rtlib/define_dependency.hpp>
#include "launcher.hpp"
class launcher
	: public i_launcher, public di::component {
private:
	component_dependencies( m_window_closed_listeners, i_window_closed_listener );
	component_dependencies( m_update_listeners, i_update_listener );
	component_dependencies( m_initialization_listeners, i_initialization_end_listener );

	component_dependency( m_scene_manager, i_scene_manager );
	component_dependency( m_logger, i_logger );
	component_dependency( m_graphics, i_graphics );
	component_dependency( m_scripting, i_scripting );

	component_dependency( m_windowing, i_windowing_library );
	component_dependency( m_graphics_context, i_graphics_context );

	component_attribute( m_window_width, unsigned int, 800 );
	component_attribute( m_window_height, unsigned int, 600 );
	component_attribute( m_window_fullscreen, bool, false );
	component_attribute( m_window_popup, bool, false );
	component_attribute( m_window_caption, std::wstring );

public:
	launcher( void ) = default;

private:
	virtual void run( void ) override {
		info( "initializing windowing..." );

		if( !m_windowing->initialize() ) {
			error( "failed to initialize windowing" );
			return;
		}

		i_render_window* w = m_windowing->get_render_window();
		if( w == nullptr ) {
			error( "failed to retrieve the render window to create" );
			return;
		}
		if( m_window_fullscreen ) {
			if( !w->create_fullscreen( m_window_caption,
				m_windowing->new_display_query()->get_primary_device()
			) ) {
				error( "failed to create fullscreen window" );
				return;
			}
		} else {
			window_style ws = window_style::decorated_window;
			if( m_window_popup ) {
				ws = window_style::popup_window;
			}
			if( !w->create( m_window_width, m_window_height, m_window_caption, ws ) ) {
				error( "failed to create window" );
				return;
			}
		}

		if( !m_graphics_context->create( w, nullptr ) ) {
			error( "failed to create graphics context" );
			return;
		}

		m_windowing->get_context_guard()->set_main_thread();
		m_windowing->get_context_guard()->make_current( m_graphics_context );
		
		for( i_initialization_end_listener* iel : m_initialization_listeners ) {
			iel->respond();
		}

		if( !m_graphics )
			swarn << "no graphics component was found!";

		if( !m_scripting )
			swarn << "no scripting component was found";

		info( "initializing graphics and scripting..." );
		if( m_graphics && m_graphics->initialize() ) {

			if( m_scripting )
				m_scripting->initialize();

			info( "loading startup scene..." );
			if( m_scene_manager->load_first() ) {
				info( "entering main loop" );

				i_render_window* rw = m_windowing->get_render_window();
				stop_watch sw;
				while( rw->is_open() ) {
					// Polling window events
					m_windowing->poll_events();

					for( i_update_listener* ls : m_update_listeners ) {
						ls->respond( sw.get() );
					}

					// Updating input manager
					m_windowing->get_input_manager()->update();

					const auto& scns = m_scene_manager->get_loaded();
					for( const auto& pp : scns ) {
						// Graphic system processing every loaded scene
						m_graphics->update_scene( pp.second->get_root().get() );
						// Scripting system doing the same..
						if( m_scripting )
							m_scripting->update_scene( pp.second->get_root().get() );
					}

					m_graphics_context->swap_buffers();
					m_graphics_context->clear_back_buffer();
				}

				for( i_window_closed_listener* ls : m_window_closed_listeners ) {
					ls->respond();
				}
				m_graphics_context->destroy();
				rw->destroy();
			} else {
				error( "failed to load startup scene" );
			}
		}
	}
};

#include <di_rtlib/register_class.hpp>
register_class( launcher );