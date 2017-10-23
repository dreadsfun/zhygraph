#include "asset_base.h"
namespace zhygraph {
	namespace asset {
		asset_base::asset_base( const string& name, const string& path )
			: mname( name ),
			mpath( path ) { }

		void asset_base::load( core::multi_thread& worker, const callback& ready ) {
			asset_state exp = asset_state::created;
			if( mstate.compare_exchange_strong( exp, asset_state::loading ) ) {
				auto loadobj = [ this ]( const callback& ready ) {
					bool r = _internal_load();
					if( r ) mstate.exchange( asset_state::loaded );
					auto rdf = ready.get();
					if( rdf ) rdf( r );
				};

				worker.push_no_result_job( loadobj, ready );
			}
		}

		void asset_base::unload( core::multi_thread& worker, const callback& ready ) {
			asset_state exp = asset_state::loaded;
			if( mstate.compare_exchange_strong( exp, asset_state::unloading ) ) {
				auto unloadobj = [ this ]( const callback& ready ) {
					bool r = _internal_unload();
					if( r ) mstate.exchange( asset_state::created );
					auto rdf = ready.get();
					if( rdf ) rdf( r );
				};

				worker.push_no_result_job( unloadobj, ready );
			}
		}

		const string& asset_base::name() const {
			return mname;
		}

		const string& asset_base::path() const {
			return mpath;
		}

		const atomic<asset_base::asset_state>& asset_base::state() const {
			return mstate;
		}
	}
}