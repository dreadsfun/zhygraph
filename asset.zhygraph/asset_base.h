#pragma once
/*
std::atomic
*/
#include <atomic>
/*
std::string
*/
#include <string>
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

			/*
			Loads the asset from the path stored in the asset
			Must set the state to loading before starting any loading operations
			Must set the state to loaded and return true if the loading is successful
			Must set the state to created and return false if the loading is unsuccessful, and the asset data remained "clean"
			Must set the state to corrupt and return false if the loading is unsuccessful, and for some reason the data could not be cleansed
			*/
			virtual bool load() = 0;

			/*
			Unloads the asset, freeing its resources
			Must set the state to unloading before starting any unloading operations
			Must set the state to created and return true if the loading is successful
			Must set the state to loaded and return false if the unloading is unsuccessful, and the asset data remained clean and usable
			Must set the state to corrupt and return false if the unloading is unsuccessful, and for some reason the data is left unusable
			*/
			virtual bool unload() = 0;

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
			asset_state state() const;
		};
	}
}