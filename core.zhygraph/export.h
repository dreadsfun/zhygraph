#pragma once
#ifndef core_shared
#  ifdef COREZHYGRAPH_EXPORTS
#    define core_shared __declspec(dllexport)
#  else
#    define core_shared __declspec(dllimport)
#  endif // ~CORE_EXPORTS
#endif // ~core_shared#pragma once
