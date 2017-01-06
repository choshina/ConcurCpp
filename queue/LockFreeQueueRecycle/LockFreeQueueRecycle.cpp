#include "LockFreeQueueRecycle.h"

LockFreeQueueRecycle::LockFreeQueueRecycle()
{
	Node* sen = new Node(-2);
	head = new AtomicStampedReference<Node>(sen,0);
	tail = new AtomicStampedReference<Node>(sen,0);
	pthread_key_create(&freeList,NULL);
	
}

void LockFreeQueueRecycle::enq(int value)
{
	Node* node = allocate(value);
	int lastStamp;
	int nextStamp;
	int newStamp;
	while(true){
		Node* last = tail->get(lastStamp);
		Node* next = last->next->get(nextStamp);
		if(last == tail->get(newStamp)&&newStamp == lastStamp){
			if(next == NULL){
				if(last->next->compareAndSet(next,node,
							nextStamp,nextStamp+1)){
					tail->compareAndSet(last,node,
							lastStamp,lastStamp+1);
					return;
				}
			
			}else{
				tail->compareAndSet(last,next,
							lastStamp,lastStamp+1);
			}
		}
	}

}

int LockFreeQueueRecycle::deq()
{
	int lastStamp;
	int firstStamp;
	int nextStamp;
	int newStamp;
	
	while(true){
		Node* first = head->get(firstStamp);
		Node* last = tail->get(lastStamp);
		Node* next = first->next->get(nextStamp);
		if(first == head->get(newStamp)&&newStamp == firstStamp){
			if(first==last){
				if(next == NULL){
					return -1;
				}	
				tail->compareAndSet(last,next,
						lastStamp,lastStamp+1);
			}else{
				int result = next->value;
				if(head->compareAndSet(first,next,
							firstStamp,firstStamp+1)){
					free(first);
					return result;
				}	
			}
		}
	}

	
}

void LockFreeQueueRecycle::free(Node* node)
{
	Node* pre = (Node *)pthread_getspecific(freeList);
	node->next = new AtomicStampedReference<Node>(pre,0);
	pthread_setspecific(freeList,(void *)node);
}

LockFreeQueueRecycle::Node* LockFreeQueueRecycle::allocate(int value)
{
//	int stamp;
	Node* node =(Node *)pthread_getspecific(freeList);
	if(node == NULL){
		node = new Node(-1);
	}else{
		pthread_setspecific(freeList,(void *)node->next->getReference());
		node->next = new AtomicStampedReference<Node>(NULL,0);
	}
	node->value = value;
	return node;
}

string LockFreeQueueRecycle::toString()
{
	Node* curr = head->getReference();
	string s = "";
	while(curr!=tail->getReference()){
		s = s + trans(curr->next->getReference()->value);
		curr = curr->next->getReference();
	}
	
	return s;
}

string LockFreeQueueRecycle::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
