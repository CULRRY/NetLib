#pragma once

#include "Types.h"
#include "Macro.h"
#include "TLS.h"

#include <windows.h>
#include <iostream>
#include <thread>
using namespace std;

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")