#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <string>
#include <functional>
#include <cassert>
#include <core.zhygraph\multi_thread.h>
#include <core.zhygraph\config.h>
#include "asset_base.h"
#include "asset_pointer.h"
#include "export.h"
namespace zhygraph {
	namespace asset {
		class asset_pointer;
		class asset_manager;

		class asset_factory {
		private:
			using asset_factory_map = unordered_map<string, function<asset_base*( const string&, const string& )>>;
			asset_factory_map mfactorymap;

		public:
			template<typename T>
			void registertype( const string& tname ) {
				mfactorymap[ tname ] = []( const string& id, const string& p) {
					return static_cast< asset_base* >( new T( id, p ) );
				}
			}

			asset_pointer create( asset_manager* owner, const string& tname, const string& id, const string& p );

			const asset_factory_map& types() const {
				return mfactorymap;
			}
		};

		class asset_manager {
		private:
			typedef unordered_map<string, asset_pointer> asset_id_map;
			/*
			serves as a gc list, so the pointer wrapper is not used here
			only the raw pointer
			*/
			typedef map<uint32_t, asset_base*> asset_memory_map;

		public:
			enum class gc_policy {
				least_freed_object,
				leave_biggest_object
			};

		private:
			core::multi_thread mglworker;
			core::multi_thread_distributor mworkers;

			asset_id_map massets;
			asset_memory_map mgclist;

			asset_factory mfactory;

			uint32_t mworkercount { 1 };
			gc_policy mgcpolicy { gc_policy::least_freed_object };

		public:
			asset_shared asset_manager( const asset_factory& f );
			asset_shared core::multi_thread* worker( bool glthread, bool idle );
			void notify_unreferenced( asset_base* asset );
			asset_shared void initialize( const core::config::_group& grp, const core::config& assets );
			asset_shared asset_pointer asset( const string& id );
		};

		typedef std::shared_ptr<asset_manager> asset_manager_ptr;
	}
}