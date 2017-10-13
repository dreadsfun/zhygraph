#pragma once
#include <cstdint>
#include <memory>
#include "zhy_exception.h"
namespace zhygraph {
	namespace core {
		using namespace std;
		/*
		represents the state, one asset currently resides in
		state-transition diagram:
										iasset_loader::create()
		(asset object does not exist) --------------------------> asset_state::created
																^	|
								  iasset_system::unload_asset() |	| iasset_system::load_asset()
								|--------------------------------	|
								|		(async loading completes)	¡
				  asset_state::loaded <-------------------------- asset_state::loading
		*/
		enum class asset_state {
			created,
			loading,
			loaded,
			unloading
		};
		class iasset_loader;
		/*
		base for every kind of assets
		*/
		class asset_base {
		private:
			asset_state mstate;
			string mname;
			string mpath;
		public:
			asset_state state() const {
				return mstate;
			}
			const string& name() const {
				return mname;
			}
			const string& path() const {
				return mpath;
			}
		};
		class asset_nullptr_exception
			: public core::exception { 
		public:
			asset_nullptr_exception() {
				_s() << "asset pointer was nullptr";
			}
			asset_nullptr_exception(const char* file, int line)
				: core::exception( file, line ) {
				_s() << "asset pointer was nullptr";
			}
		};
		class asset_pointer {
		private:
			asset_base* mpasset { nullptr };
			uint64_t* mpref_count { nullptr };
		public:
			asset_pointer( asset_base* ptr = nullptr )
				: mpasset( ptr ) { 
				if( mpasset != nullptr ) {
					mpref_count = new uint64_t( 1 );
				}
			}
			asset_pointer( const asset_pointer& cpy )
				: mpasset( cpy.mpasset ),
				mpref_count( cpy.mpref_count ) {
				if( mpasset != nullptr ) {
					( *mpref_count )++;
				}
			}
			asset_pointer( asset_pointer&& mv )
				: mpasset( mv.mpasset ),
				mpref_count( mv.mpref_count ) {
				mv.mpasset = nullptr;
				mv.mpref_count = nullptr;
			}
			~asset_pointer() {
				if( --( *mpref_count ) == 0 ) {
					delete mpref_count;
				}
			}
			uint64_t ref_count() const {
				if( mpasset != nullptr ) {
					return *mpref_count;
				} else {
					return 0;
				}
			}
			asset_base* operator -> () {
				dbg_throw_if( mpasset == nullptr, asset_nullptr_exception );
				return mpasset;
			}
			const asset_base* operator -> () const {
				dbg_throw_if( mpasset == nullptr, asset_nullptr_exception );
				return mpasset;
			}
			asset_base& operator * () {
				dbg_throw_if( mpasset == nullptr, asset_nullptr_exception );
				return *mpasset;
			}
			const asset_base& operator * () const {
				dbg_throw_if( mpasset == nullptr, asset_nullptr_exception );
				return *mpasset;
			}
		};
		/*
		must be implemented for every type of asset
		implements the actual loading and creation algorithm of the selected type of asset
		*/
		class iasset_loader {
		public:
			virtual ~iasset_loader() = default;
			/*
			creates an asset with the specified name, linked to the file, on the specified path
			if the file does not exist, it is created
			*/
			virtual asset_base* create( const string& name, const string& path ) = 0;
			/*
			returns the currently loaded asset
			*/
			virtual asset_pointer asset() = 0;
			/*
			switches the currently loaded asset to the specified one
			only affects the currently loaded instance, if the new one is fully loaded and usable
			*/
			virtual asset_pointer load( const string& name ) = 0;
			virtual asset_pointer load( const string& name, const string& path ) = 0;
		};
		/*
		stores every created asset, and manages their lifetime/loading/unloading processes
		does NOT implements the actual loading algorithm of the different type of assets
		*/
		class iasset_system {
		public:
			virtual ~iasset_system() = default;
			/*
			searches for the specified asset in the asset store and loads it if it is not loaded already
			if the specified asset does not exist the loader's create method is called, and then the asset is loaded
			if path is not specified and the asset does not exist already, the loading will fail
			*/
			virtual asset_pointer load( iasset_loader* loader, const string& name ) = 0;
			virtual asset_pointer load( iasset_loader* loader, const string& name, const string& path ) = 0;
			/*
			requests the unloading of the specified asset, which will happen instantly
			automatic unloading happens from the garbage list if the memory limit is exceeded
			*/
			virtual void unload( const string& name ) = 0;
			virtual void unload( asset_pointer asset ) = 0;
			/*
			getter and setter for the maximum memory properties of the asset system
			when the maximum memory usage of the system is reached, it is excepted from the asset system
			to unload assets from its garbage list
			*/
			virtual uint64_t maxmemory() const = 0;
			virtual void maxmemory( uint64_t val ) = 0;
			/*
			returns the memory used by the asset system
			includes every asset instance size and their loaded data size
			*/
			virtual uint64_t usedmemory() const = 0;
			/*
			explicit request for garbage collection
			returns the number of bytes freed
			*/
			virtual uint64_t garbage() = 0;
		};
	}
}