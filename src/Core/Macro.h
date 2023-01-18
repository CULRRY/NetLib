#pragma once


/// @brief 변수의 크기를 int16 형태로 반환해주는 매크로.
#define SIZE16(val) static_cast<int16>(sizeof(val))

/// @brief 변수의 크기를 int32 형태로 반환해주는 매크로.
#define SIZE32(val) static_cast<int32>(sizeof(val))

/// @brief 배열의 길이를 int16 형태로 반환해주는 매크로.
#define LEN16(arr)	static_cast<int16>(sizeof(arr) / sizeof(arr[0])

/// @brief 배열의 길이를 int32 형태로 반환해주는 매크로.
#define LEN32(arr)	static_cast<int32>(sizeof(arr) / sizeof(arr[0])

/// @brief 강제로 크래쉬를 발생시키는 매크로.
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xFFFFFFFF;					\
}

/// @brief 조건식이 거짓일 경우에 강제로 크래쉬를 발생시키는 매크로.
#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}