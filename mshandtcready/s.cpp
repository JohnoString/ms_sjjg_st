#if 0
#include <iostream>
#include <windows.h>
using namespace std;

// 生产者消费者
// 读写锁
// 包解析死锁问题

class byLock
{
public:
	byLock();
	~byLock();

	void Lock();
	void Unlock();

private:

#ifdef __LINUX__
	pthread_mutex_t m_Mutex;
#else
	CRITICAL_SECTION m_cs;
#endif
	bool m_bLocked;
};

/////////////////////////////////////////////
byLock::byLock()
{
#ifdef __LINUX__
	pthread_mutex_init(&m_Mutex, NULL);
#else
	::InitializeCriticalSection(&m_cs);
#endif
	m_bLocked = false;
}
byLock::~byLock()
{
	if (m_bLocked)
		Unlock();

#ifdef __LINUX__
	pthread_mutex_destroy(&m_Mutex);
#else
	::DeleteCriticalSection(&m_cs);
#endif
}

void byLock::Lock()
{
#ifdef __LINUX__
	pthread_mutex_lock(&m_Mutex);
#else
	::EnterCriticalSection(&m_cs);
#endif
	m_bLocked = true;
}
void byLock::Unlock()
{
#ifdef __LINUX__
	pthread_mutex_unlock(&m_Mutex);
#else
	::LeaveCriticalSection(&m_cs);
#endif
	m_bLocked = false;
}

/////////////////////////////////////////////

class byAutoLock
{
public:
	byAutoLock(byLock* pbylock)
	{
		m_pbyLock = pbylock;

		if (m_pbyLock)
			m_pbyLock->Lock();
	}

	~byAutoLock()
	{
		if (m_pbyLock)
			m_pbyLock->Unlock();

		m_pbyLock = NULL;
	}

private:
	byLock* m_pbyLock;
};

byLock bL1, bL2;

int FlowTestProtoAndInit(int i)
{
	i = 3;
	return i;
}

void GetFlow()
{
	int i = 0;
	byAutoLock _alck(&bL1);

	i = 1;
	do
	{
		byAutoLock _alck(&bL1);
		FlowTestProtoAndInit(i);
	} while (0);

	i--;
}

int main()
{
	for (int i = 0; i < 100000; ++i)
	{
		GetFlow();
		printf("i=%d", i);
	}
	
	return 0;
}
#endif