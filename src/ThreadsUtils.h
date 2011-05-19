#ifndef TR_THREADS_UTILS_H
#define TR_THREADS_UTILS_H

#include <pthread.h>

namespace Thread
{
	const unsigned int MaxThreads = 30; // Not used

	void InitMutex(pthread_mutex_t* Mutex);
	void DestroyMutex(pthread_mutex_t* Mutex);
	void LockMutex(pthread_mutex_t* Mutex);
	void UnlockMutex(pthread_mutex_t* Mutex);

	bool New(pthread_t* id, void* (*function)(void*),void* Parameter);
	bool Cancel(pthread_t id);
	void Join(pthread_t id);
	void Exit();
}
#endif

//pthread_create(&callThd[i], &attr, dotprod, (void *)i);
//pthread_join(callThd[i], &status);
