#include "LockFreeQueue.h"

LockFreeQueue::LockFreeQueue()
{
	Node* sen = new Node(-1);
	head = new AtomicReference<Node>(sen);
	tail = new AtomicReference<Node>(sen);
}

void LockFreeQueue::enq(int x)
{
	Node* node = new Node(x);
	while(true){
		Node* last = tail->get();
		Node* next = last->next->get();
		if(last ==  tail->get()){
			if(next == NULL){
				if(last->next->compareAndSet(next,node)){
					tail->compareAndSet(last,node);
					return;
				}

			}else{
				tail->compareAndSet(last,next);
			}	
		}
	}
}

int LockFreeQueue::deq()
{
	while(true){
		Node* first = head->get();
		Node* last = tail->get();
		Node* next = first->next->get();
		if(first == head->get()){
			if(first == last){
				if(next == NULL){
					return -1;
				}
				tail->compareAndSet(last,next);
			}else{
				int result = next ->value;
				if(head->compareAndSet(first,next))
					return result;
			}
		}
	}
		
}

string LockFreeQueue::toString()
{
	string s = "";
	Node* curr = head->get()->next->get();
	while(curr!=NULL){
		s = s+trans(curr->value);
		curr = curr->next->get();
	}
	return s;
}

string LockFreeQueue::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
