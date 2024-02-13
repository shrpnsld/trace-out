#pragma once

#include "trace-out/platform-detection.hpp"

#if defined(TRACE_OUT_WINDOWS) // [amalgamate:remove]

#include <WinSock2.h> // [amalgamate:leave]
#include <ws2tcpip.h> // [amalgamate:leave]
#include <Windows.h> // [amalgamate:leave]

#endif // defined(TRACE_OUT_WINDOWS) // [amalgamate:remove]

