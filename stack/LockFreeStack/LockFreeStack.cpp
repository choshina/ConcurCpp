#include "LockFreeStack.h"


LockFreeStack::LockFreeStack()
{
	top =new AtomicReference<Node>(NULL);
	MIN_DELAY = 200;
	MAX_DELAY = 2000;
	backoff = new Backoff(MIN_DELAY,MAX_DELAY);
	
}



void LockFreeStack::push(int value)
{
	Node* node = new Node(value);
	while(true){
		if(tryPush(node)){
			return;
		}else{
			backoff->backoff();
		}
	}
}

bool LockFreeStack::tryPush(Node* node)
{
	Node* oldTop = top->get();
	node->next = oldTop;
	return (top->compareAndSet(oldTop,node));
}

LockFreeStack::Node* LockFreeStack::tryPop()
{
	Node* oldTop = top->get();
	if(oldTop == NULL){
		return NULL;
	}
	Node* newTop = oldTop->next;
	if(top->compareAndSet(oldTop,newTop)){
		return oldTop;
	}else{
		return NULL;
	}
}

int LockFreeStack::pop()
{
	while(true){
		Node* node = tryPop();
		if(node!= NULL){
			return node->value;
		}else{
			backoff->backoff();
		}
	}
}


