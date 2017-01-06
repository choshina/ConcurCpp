#ifndef ELIMINATIONARRAY_H_
#define ELIMINATIONARRAY_H_
#include "LockFreeExchanger.h"

class EliminationArray{
private:
	static const long duration = 2000;
	LockFreeExchanger* exchanger;
public:
	EliminationArray();
	int* visit(int* value);
};

#endif


