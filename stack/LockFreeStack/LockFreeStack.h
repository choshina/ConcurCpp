#ifndef LOCKFREESTACK_H_
#define LOCKFREESTACK_H_

#include "AtomicReference.h"
#include "Backoff.h"

class LockFreeStack{
private:
	class Node{
	public:
		int value;
		Node* next;
		Node(int m_value){
			value = m_value;
			next = NULL;
		}
	};
	AtomicReference<Node>* top;
	int MIN_DELAY;
	int MAX_DELAY;
	Backoff* backoff;
	bool tryPush(Node* node);
	Node* tryPop();
public:
	LockFreeStack();
//	bool tryPush(Node* node);
	void push(int value);
	int pop();
	
};

#endif
