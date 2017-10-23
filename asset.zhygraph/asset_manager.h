#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <string>
#include <core.zhygraph\multi_thread.h>
#include "asset_base.h"
namespace zhygraph {
	namespace asset {
		class asset_pointer;

		class asset_manager {
		private:
			typedef unordered_map<string, asset_pointer> asset_id_map;
			typedef map<uint32_t, asset_base*> asset_memory_map;

			core::multi_thread mglworker;
			core::multi_thread_distributor mworkers;

			asset_id_map massets;
			asset_memory_map mgclist;

		public:
			core::multi_thread* worker( bool glthread, bool idle );
			void notify_unreferenced( asset_base* asset );
		};

		typedef std::shared_ptr<asset_manager> asset_manager_ptr;
	}
}