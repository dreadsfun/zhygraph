#pragma once
#include <core.zhygraph\zhy_asset_system.h>
#include <unordered_map>
#include <list>
namespace zhygraph {
	namespace asset {
		using namespace core;
		using namespace std;
		class asset_system
			: public iasset_system {
		private:
			using asset_map_t = unordered_map<string, asset_pointer>;
			using garbage_list_t = list<asset_pointer>;
			uint64_t mmaxmemory;
			uint64_t musedmemory { 0 };
			asset_map_t massets;
		public:
			asset_system( uint64_t maxmem = numeric_limits<uint64_t>::max() )
				: mmaxmemory( maxmem ) { }
			virtual asset_pointer load( iasset_loader* loader, const string& name ) override;
			virtual asset_pointer load( iasset_loader* loader, const string& name, const string& path ) override;
			virtual void unload( const string& name ) override;
			virtual void unload( asset_pointer asset ) override;
			virtual uint64_t maxmemory() const override;
			virtual void maxmemory( uint64_t val ) override;
			virtual uint64_t usedmemory() const override;
			virtual uint64_t garbage() override;
		};
	}
}