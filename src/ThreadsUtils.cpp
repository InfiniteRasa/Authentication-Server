#include "ThreadsUtils.h"

	void Thread::InitMutex(pthread_mutex_t* Mutex)
	{
		pthread_mutex_init(Mutex, NULL);
	}

	void Thread::DestroyMutex(pthread_mutex_t* Mutex)
	{
		pthread_mutex_destroy(Mutex);
	}

	void Thread::LockMutex(pthread_mutex_t* Mutex)
	{
		pthread_mutex_lock(Mutex);
	}

	void Thread::UnlockMutex(pthread_mutex_t* Mutex)
	{
		pthread_mutex_unlock(Mutex);
	}

	bool Thread::New(pthread_t* id, void* (*function)(void*),void* Parameter)
	{
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		if (pthread_create(id, &attr, function, Parameter) != 0)
		{
			pthread_attr_destroy(&attr);
			return false;
		}
		pthread_attr_destroy(&attr);
		Thread::IncreaseCount();
		return true;
	}

	bool Thread::Cancel(pthread_t id)
	{
		if (pthread_cancel(id) != 0)
		{
			return false;
		}
		Thread::DecreaseCount();
		return true;
	}

	void Thread::Join(pthread_t id)
	{
		void* status;
		pthread_join(id, &status);
	}

	void Thread::Exit()
	{
		Thread::DecreaseCount();
		pthread_exit((void*) 0);
	}

	unsigned int Thread::Count()
	{
		return Thread::ThreadsCount;
	}

	void Thread::IncreaseCount()
	{
		Thread::LockMutex();
		Thread::ThreadsCount += 1;
		Thread::UnlockMutex();
	}

	void Thread::DecreaseCount()
	{
		Thread::LockMutex();
		Thread::ThreadsCount -= 1;
		Thread::UnlockMutex();
	}