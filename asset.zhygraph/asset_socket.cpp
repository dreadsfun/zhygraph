#include "asset_socket.h"
namespace zhygraph {
	namespace asset {
		asset_socket::asset_socket( asset_manager_ptr owner )
			: mcurrent( owner.get() ),
			mdesired( owner.get() ) { }

		asset_socket::asset_socket( asset_manager_ptr owner, asset_pointer current )
			: mcurrent( current ),
			mdesired( owner.get() ) { }

		void asset_socket::swap( asset_pointer desired ) {
			if( desired != mcurrent && desired != mdesired ) {
				mdesired = desired;
				asset_base::callback swapper(
					[ this ]( bool result ) {
					if( result ) {
						mcurrent = mdesired;
						mdesired.swap( nullptr );
					}
				});
				core::multi_thread* w = mdesired.owner()->worker( mdesired->gl_asset(), false );
				if( w != nullptr ) mdesired->load( *w, swapper );
			}
		}
	}
}