set(TRACE_OUT_USE_PCH NO CACHE BOOL "Use precompiled headers")
set(TRACE_OUT_USE_UNITY_BUILDS "0" CACHE STRING "Use unity builds")
set(TRACE_OUT_USE_CCACHE NO CACHE BOOL "Use 'ccache'")

include(precompiled-headers)
include(ccache)

