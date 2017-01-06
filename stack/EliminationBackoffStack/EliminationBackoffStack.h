#ifndef ELIMINATIONBACKOFFSTACK
#define ELIMINATIONBACKOFFSTACK

#include "EliminationArray.h"

class EliminationBackoffStack{
private:
//	static int capacity = 2;
	EliminationArray* eliminationArray;
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
	bool tryPush(Node* node);
	Node* tryPop();
public:
	EliminationBackoffStack();
	void push(int value);
	int pop();
};

#endif
