#pragma once
#include <string>
#include "export.h"
namespace zhygraph {
	namespace core {
		using namespace std;

		class application_root {
		private:
			string massetfile;
			string mconfigfile;
			string mscenefile;

		public:
			core_shared application_root( const string& assetfile, const string& config, const string& scenes );
			void core_shared initialize();
			void core_shared run();
		};
	}
}