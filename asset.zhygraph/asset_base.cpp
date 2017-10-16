#include "asset_base.h"
namespace zhygraph {
	namespace asset {
		asset_base::asset_base( const string& name, const string& path )
			: mname( name ),
			mpath( path ) { }

		const string& asset_base::name() const {
			return mname;
		}

		const string& asset_base::path() const {
			return mpath;
		}

		asset_base::asset_state asset_base::state() const {
			return mstate.load();
		}
	}
}