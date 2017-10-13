#include "zhy_asset_system_impl.h"
namespace zhygraph {
	namespace asset {
		asset_pointer asset_system::load( iasset_loader* loader, const string& name ) {
			return asset_pointer();
		}
		asset_pointer asset_system::load( iasset_loader* loader, const string& name, const string& path ) {
			return asset_pointer();
		}
		void asset_system::unload( const string& name ) {
		}
		void asset_system::unload( asset_pointer asset ) {

		}
		uint64_t asset_system::maxmemory() const {
			return mmaxmemory;
		}
		void asset_system::maxmemory( uint64_t val ) {
			if( mmaxmemory > val ) {
				this->garbage();
			}
			mmaxmemory = val;
		}
		uint64_t asset_system::usedmemory() const {
			return musedmemory;
		}
		uint64_t asset_system::garbage() {
			return uint64_t();
		}
	}
}