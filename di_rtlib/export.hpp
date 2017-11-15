#pragma once
#ifndef DI_SHARED
#  ifdef DI_RTLIB_EXPORTS
#    define DI_SHARED __declspec(dllexport)
#  else
#    define DI_SHARED __declspec(dllimport)
#  endif // ~DI_RTLIB_EXPORTS
#endif // ~DI_SHARED