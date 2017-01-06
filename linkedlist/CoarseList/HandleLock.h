#ifndef HANDLELOCK_H_
#define HANDLELOCK_H_

#include "MyLock.h"

class HandleLock{
private:
	MyLock* lock;
public:
	HandleLock(MyLock* ml){
		lock = ml;
		lock->lock();
	}
	~HandleLock(){
		lock->unlock();
	}

};

#endif
