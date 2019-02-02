#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef _WIN32
#include <sys/time.h>
#include <unistd.h>
#endif

extern pthread_mutex_t gMutex;

namespace Thread
{
	static unsigned int ThreadsCount = 1;
	static pthread_mutex_t* Mutex = &gMutex;
	void InitMutex(pthread_mutex_t* Mutex = Thread::Mutex);
	void DestroyMutex(pthread_mutex_t* Mutex = Thread::Mutex);
	void LockMutex(pthread_mutex_t* Mutex = Thread::Mutex);
	void UnlockMutex(pthread_mutex_t* Mutex = Thread::Mutex);

	bool New(pthread_t* id, void* (*function)(void*),void* Parameter);
	bool Cancel(pthread_t id);
	void Join(pthread_t id);
	void Exit();
	unsigned int  Count();
	void IncreaseCount();
	void DecreaseCount();
	
	void Wait(int millisecs);
	
	unsigned long GetTicks();
}
