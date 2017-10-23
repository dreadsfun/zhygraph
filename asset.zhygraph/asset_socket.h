#pragma once
#include "asset_pointer.h"
namespace zhygraph {
	namespace asset {
		class asset_socket {
		private:
			asset_pointer mcurrent;
			asset_pointer mdesired;

		public:
			asset_socket( asset_manager_ptr owner );
			asset_socket( asset_manager_ptr owner, asset_pointer current );
			void swap(asset_pointer desired);
		};
	}
}