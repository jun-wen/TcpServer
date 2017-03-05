#ifndef SERVER_BASE_CURRENTTHREAD_H
#define SERVER_BASE_CURRENTTHREAD_H

#include <stdint.h>

namespace server
{

namespace CurrentThread
{

	extern __thread int t_cachedTid;
	extern __thread char t_tidString[32];
	extern __thread int t_tidStringLength;
	extern __thread const char* t_threadName;

	void cacheTid();

	inline int tid()
	{
		//类似unlikely
		if (__builtin_expect(t_cachedTid == 0, 0))
		{
			cacheTid();
		}

		return t_cachedTid;
	}

	//logging
	inline const char* tidString()
	{
		return t_tidString;
	}

	inline int tidStringLength()
	{
		return t_tidStringLength;
	}

	inline const char* name()
	{
		return t_threadName;
	}

	bool isMainThread();

	void sleepUsec(int64_t usec);
}
}


#endif //SERVER_BASE_CURRENTTHREAD_H