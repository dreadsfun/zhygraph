#pragma once
#include <atomic>
#include <string>
#include <functional>
#include <array>
#include <list>
#include <mutex>
#include <core.zhygraph\multi_thread.h>
namespace zhygraph {
	namespace asset {
		using namespace std;
		/*
		Base class for every kinds of assets, such as texture, shader or mesh
		*/
		class asset_base {
		public:
			/*
			An asset may be in one of the following states:
			created, when the object itself was instantiated or after successful unload or after unsuccessful load
			loading, when the loading of the asset has started, but not finished yet
			loaded, when the loading of the asset ended successfully
			unloading, when the unloading of the asset has started, but not finished yet
			corrupt, when the implementation defined data structures are corrupted due to erroneous loading or unloading operations
			*/
			enum class asset_state {
				created,
				loading,
				loaded,
				unloading,
				corrupt
			};

			typedef function<void(bool)> void_fn_t;

			class callback {
			private:
				void_fn_t mfn;

			public:
				callback() = default;

				template<typename T, typename ... Args>
				callback( T fn, Args ... args ) {
					mfn = bind( fn, args ..., placeholders::_1 );
				}

				const void_fn_t& get() const {
					return mfn;
				}
			};

		private:
			/*
			The current state of this asset
			The state is updated with atomic operations to provide thread safety
			*/
			atomic<asset_state> mstate;

			/*
			Name of this asset
			Preferably a unique identifier
			*/
			string mname;

			/*
			Path to the file, associated with this asset
			*/
			string mpath;

		public:
			/*
			Construct the asset with the specified name and path
			Does not initiate any other operations on the asset
			*/
			asset_base( const string& name, const string& path );

			void load( core::multi_thread& worker, const callback& ready );
			void unload( core::multi_thread& worker, const callback& ready );

			/*
			Return the name of this asset
			*/
			const string& name() const;

			/*
			Return the path associated with this asset
			*/
			const string& path() const;

			/*
			Load and return the current state of the asset
			*/
			const atomic<asset_state>& state() const;

			virtual bool gl_asset() const = 0;
			virtual uint32_t size() const = 0;

		protected:
			virtual bool _internal_load() = 0;
			virtual bool _internal_unload() = 0;
		};
	}
}