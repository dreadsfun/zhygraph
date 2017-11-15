#pragma once
#ifndef CORE_SHARED
#  ifdef CORE_EXPORTS
#    define CORE_SHARED __declspec(dllexport)
#  else
#    define CORE_SHARED __declspec(dllimport)
#  endif // ~CORE_EXPORTS
#endif // ~CORE_SHARED