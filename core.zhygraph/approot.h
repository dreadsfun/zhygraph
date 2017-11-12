#pragma once
#include <string>
#include <GLFW\glfw3.h>
#include <asset.zhygraph\asset_manager.h>
#include <core.zhygraph\config.h>
#include <core.zhygraph\logger.h>
#include "export.h"
namespace zhygraph {
	namespace core {
		using namespace std;
		using namespace asset;

		class application_root {
		private:
			string massetfile;
			string mconfigfile;
			string mscenefile;

			GLFWwindow* mcontextwindow;
			logger_ptr mlogger;
			asset_manager_ptr massetmanager;

		public:
			core_shared application_root( const string& assetfile, const string& config, const string& scenes );
			void core_shared initialize();
			void core_shared run();

		private:
			logger_ptr _init_log( const config::_group& loggrp );
			GLFWwindow* _init_window( const config::_group& wingrp );
			asset_manager_ptr _init_asset( const config::_group& assetgrp, const config& assets );
		};
	}
}