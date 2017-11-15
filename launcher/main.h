#pragma once

#ifdef LAUNCHER_EXPORTS
#  define LAUNCHER_SHARED __declspec(dllexport)
#else
#  define LAUNCHER_SHARED __declspec(dllimport)
#endif // ~LAUNCHER_EXPORTS

#include <thread>

extern "C" {
	LAUNCHER_SHARED void* launcher_thread( void );
	int LAUNCHER_SHARED launcher( void );
}