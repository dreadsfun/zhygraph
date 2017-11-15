#pragma once
#ifndef CAPI_SHARED
#  ifdef CAPI_EXPORTS
#    define CAPI_SHARED __declspec(dllexport)
#  else
#    define CAPI_SHARED __declspec(dllimport)
#  endif // ~CAPI_EXPORTS
#endif // ~CAPI_SHARED