#pragma once


/// @brief ������ ũ�⸦ int16 ���·� ��ȯ���ִ� ��ũ��.
#define SIZE16(val) static_cast<int16>(sizeof(val))

/// @brief ������ ũ�⸦ int32 ���·� ��ȯ���ִ� ��ũ��.
#define SIZE32(val) static_cast<int32>(sizeof(val))

/// @brief �迭�� ���̸� int16 ���·� ��ȯ���ִ� ��ũ��.
#define LEN16(arr)	static_cast<int16>(sizeof(arr) / sizeof(arr[0])

/// @brief �迭�� ���̸� int32 ���·� ��ȯ���ִ� ��ũ��.
#define LEN32(arr)	static_cast<int32>(sizeof(arr) / sizeof(arr[0])

/// @brief ������ ũ������ �߻���Ű�� ��ũ��.
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xFFFFFFFF;					\
}

/// @brief ���ǽ��� ������ ��쿡 ������ ũ������ �߻���Ű�� ��ũ��.
#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}