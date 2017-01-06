#ifndef LOCKFREEQUEUERECYCLE_H_
#define LOCKFREEQUEUERECYCLE_H_
#include "AtomicStampedReference.h"
#include <pthread.h>
#include <string>
#include <sstream>
class LockFreeQueueRecycle{
private:
	class Node{
	public:
		int value;
		AtomicStampedReference<Node>* next;
		Node(int m_value){
			value = m_value;
			next = new AtomicStampedReference<Node>(NULL,0);
		}
	};
	AtomicStampedReference<Node>* head;
	AtomicStampedReference<Node>* tail;
	pthread_key_t freeList;
	Node* allocate(int value);
	void free(Node*);
	string trans(int ori);
public:
	LockFreeQueueRecycle();
	void enq(int value);
	int deq();
	string toString();

};

#endif
