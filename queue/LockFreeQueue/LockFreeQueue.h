#ifndef LOCKFREEQUEUE_H_
#define LOCKFREEQUEUE_H_

#include <string>
#include <sstream>
#include "AtomicReference.h"

using namespace std;

class LockFreeQueue{
private:
	class Node{
	public:
		int value;
		AtomicReference<Node>* next;
		Node(int m_value){
			value = m_value;
			next = new AtomicReference<Node>(NULL);
		}	
	};
	AtomicReference<Node>* head;
	AtomicReference<Node>* tail;
	string trans(int ori);
public:
	LockFreeQueue();
	void enq(int value);
	int deq();
	string toString();
};

#endif
