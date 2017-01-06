#include "MyLock.h"

MyLock::MyLock()
{
	pthread_mutex_init(&mutex,NULL);
}

MyLock::~MyLock()
{

//	if(pthread_mutex_destroy(&mutex) == EBUSY)
//		pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
}

void MyLock::lock()
{
	pthread_mutex_lock(&mutex);
}

void MyLock::unlock()
{
	pthread_mutex_unlock(&mutex);
}

