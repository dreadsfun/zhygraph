#pragma once
#include <stdint.h>
#include <memory>
#include <core.zhygraph\exception.h>
#include "asset_base.h"
#include "export.h"
namespace zhygraph {
	namespace asset {
		class asset_manager;

		class asset_pointer {
		private:
			asset_base* mpasset { nullptr };
			uint32_t* mpref_count { nullptr };
			asset_manager* mowner;

		public:
			asset_shared asset_pointer( asset_manager* owner );
			asset_shared asset_pointer( asset_manager* owner, asset_base* asset );
			asset_shared asset_pointer( const asset_pointer& ptr );
			asset_shared ~asset_pointer();
			asset_base* operator -> ();
			const asset_base* operator -> () const;
			asset_pointer& operator = ( const asset_pointer& ptr );
			bool operator != ( const asset_pointer& ptr ) const;
			bool operator == ( const asset_pointer& ptr ) const;
			asset_base* get();
			const asset_base* get() const;
			uint32_t ref() const;
			void swap( asset_base* asset );
			asset_manager* owner();
		};

		class asset_nullptr_exception
			: public core::exception {
		public:
			asset_nullptr_exception( const char* file, int line );
		};
	}
}