#ifndef LOCKFREEEXCHANGER
#define LOCKFREEEXCHANGER
#include "AtomicStampedReference.h"
#include <time.h>

class LockFreeExchanger{
private:
	enum stamp{EMPTY = 2001,WAITING = 2002,BUSY = 2003};
	AtomicStampedReference<int>* slot;
public:
	int* exchange(int* myItem,long timeout);
	LockFreeExchanger(){
		slot = new AtomicStampedReference<int>(NULL,0);
	}

};

#endif
