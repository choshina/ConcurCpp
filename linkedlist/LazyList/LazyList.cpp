#include "LazyList.h"
//contains calls are wait-free
//


LazyList::LazyList()
{
	head = new Node(MIN_VALUE);
	tail = new Node(MAX_VALUE);
	head->next = tail;

}

bool LazyList::add(int value)
{

	Node* pred;
	Node* curr;
	HandleNode hn1(&pred);
	HandleNode hn2(&curr);
	while(true){		
		pred = head;
		curr = pred->next;
		while(curr->value < value){
			pred = curr;
			curr = curr->next;
		}
		pred->lock();
		curr->lock();
		if(validate(pred,curr)){
			if(curr ->value == value){
//				*re = 0;
//				break;
				return false;
			}else{
				Node* node = new Node(value);
				node->next = curr;
				pred->next = node;	
		//		*re = 1;
		//		break;
				return true;
			}
		}else{
			curr->unlock();
			pred->unlock();
		}
	}	
//	curr->unlock();
//	pred->unlock();
	
	
}

bool LazyList::remove(int value)
{
	Node* pred;
	Node* curr;
	HandleNode hn1(&pred);
	HandleNode hn2(&curr);
	while(true){		
		pred = head;
		curr = head->next;
		while(curr->value < value){

			pred = curr;
			curr = curr->next;
		}
		pred->lock();
		curr->lock();
		if(validate(pred, curr)){
			if(curr->value == value){
				curr->mark = true;
				pred->next = curr->next;
			
	//			*re = 1;
	//			break;
				return true;
			}else{
			//	*re = 0;
			//	break;
				return false;
			}
		}else{
			curr->unlock();
			pred->unlock();
		}
	
	}	
	//	curr->unlock();
	//	pred->unlock();
		
}

bool LazyList::contains(int value)
{
	Node* curr = head->next;
	while(curr->value < value){
		curr = curr->next;
	}	
	if(curr->value == value&&!curr->mark)
	//	*re = 1;
		return true;
	else
	//	*re = 0;
		return false;
}

bool LazyList::validate(Node* pred, Node* curr)
{
	return (!pred->mark)&&(!curr->mark)&&(pred->next==curr);
}

string LazyList::toString()
{
	string s = "";
	Node* curr = head->next;
	while(curr->value != MAX_VALUE){
		s = s + trans(curr->value);
		s = s + '\n';
		curr = curr->next;
	}
	return s;
}

string LazyList::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
