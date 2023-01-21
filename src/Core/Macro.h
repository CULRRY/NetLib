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

/// @brief Ŭ���� ������ ����� �������� ���� �������ִ� ��ũ��.
#define USE_MANY_LOCKS(count)	Lock _locks[count];

/// @brief Ŭ���� ������ ����� ���� �������ִ� ��ũ��. 
#define USE_LOCK				USE_MANY_LOCKS(1);

/// @brief idx��° ReadLock�� ��� ��ũ��.
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx], typeid(this).name());

/// @brief �Ѱ��� ���� ����Ҷ�, ReadLock�� ��� ��ũ��.
#define READ_LOCK				READ_LOCK_IDX(0);

/// @brief idx��° WriteLock�� ��� ��ũ��.
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx], typeid(this).name());

/// @brief �Ѱ��� ���� ����Ҷ�, WriteLock�� ��� ��ũ��.
#define WRITE_LOCK				WRITE_LOCK_IDX(0);