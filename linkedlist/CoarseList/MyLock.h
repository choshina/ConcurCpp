#ifndef MYLOCK_H_
#define MYLOCK_H_

#include <pthread.h>

class MyLock{
private:
	pthread_mutex_t mutex;
public:
	MyLock();
	~MyLock();
	void lock();
	void unlock();
};

#endif
