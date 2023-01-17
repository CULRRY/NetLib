#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Core\\Debug\\Core.lib")
#else
#pragma comment(lib, "Core\\Release\\Core.lib")
#endif

#include "Common.h"