#include "MyThread.h"


void* help_run(void* arg)
{
	((MyThread*)arg)->run();
}

MyThread::MyThread()
{

}

void MyThread::start()
{
	pthread_create(&p,NULL,help_run,this);
}

void MyThread::join()
{
	pthread_join(p,NULL);
}

