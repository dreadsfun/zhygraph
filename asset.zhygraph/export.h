#pragma once
#ifndef asset_shared
#  ifdef ASSETZHYGRAPH_EXPORTS
#    define asset_shared __declspec(dllexport)
#  else
#    define asset_shared __declspec(dllimport)
#  endif // ~ASSETZHYGRAPH_EXPORTS
#endif // ~asset_shared