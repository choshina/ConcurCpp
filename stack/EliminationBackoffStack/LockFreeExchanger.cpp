#include "LockFreeExchanger.h"
//超时-2
//错误-3
int* LockFreeExchanger::exchange(int* myItem,long timeout)
{
	clock_t startTime = clock();
	clock_t currentTime;
	int stampHolder = EMPTY;
	
	
	while(true){
		///////////////////
		currentTime = clock();
		if(((currentTime - startTime)/CLOCKS_PER_SEC)*1000 >timeout)
			return myItem;
		
		int* yourItem = slot->get(stampHolder);
		int stamp = stampHolder;
		switch(stamp){
		case EMPTY:
			if(slot->compareAndSet(yourItem,myItem,EMPTY,WAITING)){
				currentTime = clock();
				while(((currentTime - startTime)/CLOCKS_PER_SEC)*1000 < timeout){
					yourItem = slot->get(stampHolder);
					if(stampHolder == BUSY){
						slot->set(NULL,EMPTY);
						return yourItem;
					}
					currentTime = clock();
				}
				if(slot->compareAndSet(myItem,NULL,WAITING,EMPTY)){
					return myItem;
				}else{
					yourItem = slot->get(stampHolder);
					slot->set(NULL,EMPTY);
					return yourItem;
				}
				
				
				
			}
			break;
		case WAITING:
			if(slot->compareAndSet(yourItem,myItem,WAITING,EMPTY))
				return yourItem;
			break;
		case BUSY:
			break;
	
		}
		
	
	}
}
