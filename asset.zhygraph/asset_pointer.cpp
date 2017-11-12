#include "asset_pointer.h"
#include "asset_manager.h"
namespace zhygraph {
	namespace asset {
		asset_pointer::asset_pointer( asset_manager* owner )
			: mowner( owner ) { }

		asset_pointer::asset_pointer( asset_manager* owner, asset_base* asset )
			: mowner( owner ) {
			if( asset != nullptr ) {
				mpasset = asset;
				mpref_count = new uint32_t( 1 );
			}
		}

		asset_pointer::asset_pointer( const asset_pointer& ptr )
			: mpref_count( ptr.mpref_count ),
			mpasset( ptr.mpasset ),
			mowner( ptr.mowner ) {
			if( mpref_count != nullptr ) {
				*mpref_count++;
			}
		}

		asset_pointer::~asset_pointer() {
			if( mpref_count != nullptr ) {
				delete mpref_count;
				mpref_count = nullptr;
			}
		}

		asset_base* asset_pointer::operator->() {
			throw_if( mpasset == nullptr, asset_nullptr_exception );
			return mpasset;
		}

		const asset_base* asset_pointer::operator->() const {
			throw_if( mpasset == nullptr, asset_nullptr_exception );
			return mpasset;
		}

		asset_pointer& asset_pointer::operator=( const asset_pointer& ptr ) {
			if( ptr.mpasset != nullptr ) {
				mpasset = ptr.mpasset;
				if( mpref_count != nullptr ) {
					if( --*mpref_count == 0 ) {
						mowner->notify_unreferenced( mpasset );
						delete mpref_count;
					}
				}
				mpref_count = ptr.mpref_count;
				*mpref_count++;
			}
			return *this;
		}

		bool asset_pointer::operator!=( const asset_pointer& ptr ) const {
			return ptr.mpasset != mpasset;
		}

		bool asset_pointer::operator==( const asset_pointer& ptr ) const {
			return ptr.mpasset == mpasset;
		}

		asset_base* asset_pointer::get() {
			return mpasset;
		}

		const asset_base* asset_pointer::get() const {
			return mpasset;
		}

		uint32_t asset_pointer::ref() const {
			/*
			ref counter pointer may only be nullptr if the asset pointer is nullptr
			*/
			throw_if( mpref_count == nullptr, asset_nullptr_exception );
			return *mpref_count;
		}

		void asset_pointer::swap( asset_base* asset ) {
			if( mpref_count != nullptr ) {
				if( --*mpref_count == 0 ) {
					mowner->notify_unreferenced( mpasset );
					delete mpref_count;
				}
			}

			if( asset != nullptr ) {
				mpref_count = new uint32_t( 1 );
				mpasset = asset;
			}
		}

		asset_manager* asset_pointer::owner() {
			return mowner;
		}

		asset_nullptr_exception::asset_nullptr_exception( const char* file, int line )
			: core::exception( file, line ) { }
	}
}