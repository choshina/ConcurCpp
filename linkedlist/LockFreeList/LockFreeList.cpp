#include "LockFreeList.h"
//class LockFreeList::WindowGet;

LockFreeList::LockFreeList()
{
	head = new Node(MIN_VALUE);
	tail = new Node(MAX_VALUE);
	while(!head->next->compareAndSet(NULL,tail,false,false));
}

bool LockFreeList::add(int value)
{
	WindowGet* window;
	Node* t_pred = NULL;
	Node* t_curr = NULL;
	while(true){
		window = find(head,value);
		t_pred = window->pred;
		t_curr = window->curr;
		
		if(t_curr->value != value){
			Node* newNode = new Node(value);
			newNode->next = new AtomicMarkableReference<Node>(t_curr,false);
			if(t_pred->next->compareAndSet(t_curr,newNode,false,false))
			//	*re = 1;
				return true;
		}else{
		//	*re = 0;
			return false;
		}
		
	}
}

bool LockFreeList::remove(int value)
{
	WindowGet* window = NULL;
	Node* t_pred = NULL;
	Node* t_curr = NULL;
	Node* t_succ = NULL;
	bool snip;
	while(true){
		window = find(head,value);
		t_pred = window->pred;
		t_curr = window->curr;
		if(t_curr->value == value){
//			t_curr->next->set()
			t_succ = t_curr->next->getReference();
			snip = t_curr->next->attemptMark(t_succ,true);
			if(!snip)
				continue;
			t_pred->next->compareAndSet(t_curr,t_succ,false,false);
		//	*re = 1;
			return true;
		}else{
		//	*re = 0;
			return false;
		}
	}
}

bool LockFreeList::contains(int value)
{
	Node* curr = head;
//	bool marked = false;
	while(curr->value < value){
		curr = curr->next->getReference();
		
	}
	if((curr->value == value)&&(!curr->next->isMarked()))
//		*re = 1;
		return true;
	else
//		*re = 0;
		return false;
}

LockFreeList::WindowGet* LockFreeList::find(Node* t_head,int value)
{
	Node* t_pred = NULL;
	Node* t_curr = NULL;
	Node* t_succ = NULL;
	bool marked;
	marked = false;
	int i;
	while(true){
		i = 0;
		t_pred = t_head;
		t_curr = t_head->next->getReference();
		while(true){
		//	succ = curr->get(isMarked);
			t_succ = t_curr->next->get(marked);
			while(marked){
			//	if(pred->next->compareAndSet(curr,succ,true,false){
				if(t_pred->next->compareAndSet(t_curr,t_succ,false,false)){
				//	pred = succ;
					t_curr = t_succ;
					t_succ = t_curr->next->get(marked);
				}else{
					i = 1;	
					break;
				}
				
			}	
			if(i == 1)
				break;
//			if(curr->value == value)
			if(t_curr->value>=value)
				return new WindowGet(t_pred,t_curr);
			t_pred = t_curr;
			t_curr = t_succ;
		}
	}
}

string LockFreeList::toString()
{
	Node* curr = head->next->getReference();
	string s = "";
	while(curr->value != MAX_VALUE){
		s = s + trans(curr->value);
		s = s + '\n';
		curr = curr->next->getReference();	
	}
	return s;
}

string LockFreeList::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
