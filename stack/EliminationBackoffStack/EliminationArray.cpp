#include "EliminationArray.h"

EliminationArray::EliminationArray()
{
	exchanger = new LockFreeExchanger();

	
}

int* EliminationArray::visit(int* value)
{
	//int slot = rand()%range;
	return exchanger->exchange(value,duration);
}
