#include "approot.h"
namespace zhygraph {
	namespace core {
		using namespace asset;

		application_root::application_root( const string& assetfile, const string& config, const string& scenes )
			: massetfile( assetfile ),
			mconfigfile( config ),
			mscenefile( scenes ) { }

		void application_root::initialize() {
			config main;
			main.load( mconfigfile );
			mlogger = _init_log( main.group( "log" ) );

			config assets;
			assets.load( massetfile );
			massetmanager = _init_asset( main.group( "asset_system" ), assets );

			mcontextwindow = _init_window( main.group( "window" ) );
		}

		void application_root::run() {
			while( !glfwWindowShouldClose( mcontextwindow ) ) {
				glfwSwapBuffers( mcontextwindow );
				glfwPollEvents();
			}
		}

		logger_ptr application_root::_init_log( const config::_group& loggrp ) {
			logger_ptr l = make_unique<logger>();

			if( loggrp.test( "use_stdout" ) ) {
				logchannelptr stdoutch = make_unique<stdout_channel>();
				l->channel( move( stdoutch ) );
			}

			const string& logfname = loggrp.value( "target_file" );
			if( !logfname.empty() ) {
				logchannelptr fch = make_unique<file_channel>( logfname );
				l->channel( move( fch ) );
			}

			l->log( log_priority::info, "logging has started", "application" );

			return l;
		}

		GLFWwindow* application_root::_init_window( const config::_group& wingrp ) {
			return glfwCreateWindow( 
				wingrp.integer( "width", 800 ), 
				wingrp.integer( "height", 600 ), 
				wingrp.value( "title", "ZhyGraph Launcher" ).c_str(),
				nullptr, nullptr );
		}

		asset_manager_ptr application_root::_init_asset( const config::_group& assetgrp, const config& assets ) {
			asset_factory factory;

			//factory.registertype<mesh_asset>( "mesh" );
			//factory.registertype<script_asset>( "script" );
			//factory.registertype<shader_asset>( "shader" );
			//factory.registertype<texture_asset>( "texture" );

			asset_manager_ptr assetmanager = make_unique<asset_manager>( factory );
			assetmanager->initialize( assetgrp, assets );
			return assetmanager;
		}
	}
}