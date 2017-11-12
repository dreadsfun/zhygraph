#include "asset_manager.h"
#include "asset_pointer.h"
#include <assert.h>
namespace zhygraph {
	namespace asset {
		asset_manager::asset_manager( const asset_factory& f )
			: mfactory( f ) { }

		core::multi_thread* asset_manager::worker( bool glthread, bool idle ) {
			core::multi_thread* r = &mglworker;
			if( !glthread ) {
				if( idle )
					r = mworkers.idle_thread();
				else
					r = mworkers.least_job_thread();
			}
			return r;
		}
		void asset_manager::notify_unreferenced( asset_base* asset ) {
			assert( asset );
			mgclist[ asset->size() ] = asset;
		}

		void asset_manager::initialize( const core::config::_group& grp, const core::config& assets ) {
			mworkercount = grp.integer( "loader_thread_count", mworkercount );
			mworkers.thread_count( mworkercount );
			if( grp.value( "gc_policy" ) == "leave_biggest_object" ) {
				mgcpolicy = gc_policy::leave_biggest_object;
			}

			const auto& ts = mfactory.types();
			for( const auto& ct : ts ) {
				const core::config::name_value_map& nv = assets.group( ct.first ).values();
				for( const auto& cv : nv ) {
					//massets[ cv.first ] = mfactory.create( this, ct.first, cv.first, cv.second );
					massets.insert( make_pair( cv.first, mfactory.create( this, ct.first, cv.first, cv.second ) ) );
				}
			}
		}

		asset_pointer asset_manager::asset( const string& id ) {
			auto fit = massets.find( id );
			if( fit == massets.end() ) return asset_pointer( this );
			else return fit->second;
		}

		asset_pointer asset_factory::create( asset_manager * owner, const string & tname, const string & id, const string & p ) {
			asset_base* r = nullptr;
			auto fit = mfactorymap.find( tname );
			if( fit != mfactorymap.end() )
				r = fit->second( id, p );
			return asset_pointer( owner, r );
		}
	}
}