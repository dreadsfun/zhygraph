#include "plugin.hpp"
#include "exception.hpp"
#include <Windows.h>
namespace di {
class win32library
	: public i_shared_library {
private:
	HMODULE m_handle;

public:
	win32library( const std::string& file ) {
		m_handle = LoadLibraryA( file.c_str() );
		if( m_handle == NULL ) {
			DWORD le = GetLastError();
			LPSTR estr = NULL;
			std::string reason;
			FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER
				| FORMAT_MESSAGE_IGNORE_INSERTS, NULL, le, 0, reinterpret_cast< LPSTR >( &estr ), 0, NULL );
			if( estr != NULL ) {
				reason = estr;
				LocalFree( estr );
			}
			throw library_failed_to_load( file, reason );
		}
	}
};

plugin::library_ptr plugin::_create_library( const std::string& file ) {
	return std::make_unique< win32library >( file );
}
}