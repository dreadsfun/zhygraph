#include "approot.h"
#include <asset.zhygraph\asset_manager.h>
#include <core.zhygraph\config.h>
#include <core.zhygraph\logger.h>
namespace zhygraph {
	namespace core {
		application_root::application_root( const string& assetfile, const string& config, const string& scenes )
			: massetfile( assetfile ),
			mconfigfile( config ),
			mscenefile( scenes ) { }

		void application_root::initialize() {
			logger l;
			
			config main;
			main.load( mconfigfile );

			const config::_group& loggrp = main.group( "log" );

			if( loggrp.test( "use_stdout" ) ) {
				logchannelptr stdoutch = make_unique<stdout_channel>();
				l.channel( move(stdoutch) );
			}

			const string& logfname = loggrp.value( "target_file" );
			if( !logfname.empty() ) {
				logchannelptr fch = make_unique<file_channel>( logfname );
				l.channel( move( fch ) );
			}

			l.log( log_priority::info, "logging has started", "application" );
		}

		void application_root::run() {

		}
	}
}