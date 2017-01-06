#ifndef MYTHREAD_H_
#define MYTHREAD_H_

#include <pthread.h>


class MyThread{
private:
	pthread_t p;
public:
	MyThread();
	friend void* help_run(void* arg);
	void join();
	virtual void run() = 0;
	void start();
};


#endif
