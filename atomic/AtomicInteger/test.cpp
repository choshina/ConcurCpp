#include "AtomicInteger.h"

#include <pthread.h>
using namespace std;

AtomicInteger* ai;

void* m1(void* arg)
{
	for(int i =0;i<50;i++){
		ai->getAndIncrement();
	}
}

int main()
{
	ai = new AtomicInteger(0);	

	pthread_t p1;
	pthread_t p2;
	
	pthread_create(&p1,NULL,m1,NULL);
	pthread_create(&p2,NULL,m1,NULL);
	
	pthread_join(p1,NULL);
	pthread_join(p1,NULL);
	
	cout<<ai->get();
}
