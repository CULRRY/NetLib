#pragma once

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Core\\Debug\\Core.lib")
#else
#pragma comment(lib, "Core\\Release\\Core.lib")
#endif

#include "Common.h"