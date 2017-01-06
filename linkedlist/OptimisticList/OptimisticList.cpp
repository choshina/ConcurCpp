#include "OptimisticList.h"

OptimisticList::OptimisticList()
{
	head = new Node(MIN_VALUE);
	tail = new Node(MAX_VALUE);
	head->next = tail;

}

bool OptimisticList::add(int value)
{
	Node* pred;
	HandleNode hn1(&pred);

	Node* curr;
	HandleNode hn2(&curr);
	while(true){		
		pred = head;
		curr = pred->next;
		while(curr -> value < value){
			pred = curr;
			curr = curr->next;
		}
		pred->lock();
		curr->lock();
		if(validate(pred,curr)){
			if(curr->value == value){
//				*re = 0;
//				break;
				return false;
			}else{
				Node* node = new Node(value);
				node ->next = curr;
				pred ->next = node;
//				*re = 1;
//				break;
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

bool OptimisticList::remove(int value)
{
	Node* pred;
	HandleNode hn1(&pred);
	Node* curr;	
	HandleNode hn2(&curr);
	while(true){		
		pred = head;
		curr = pred->next;

		while(curr->value < value){
			pred = curr;
			curr = curr->next;
	
		}
		pred ->lock();
		curr ->lock();
		if(validate(pred,curr)){
			if(curr->value != value){
			//	*re = 0;
			//	break;
				return false;
			}else{
				pred->next = curr->next;
			//	*re = 1;
			//	break;
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

bool OptimisticList::contains(int value)
{
	Node* pred;
	HandleNode hn1(&pred);
	Node* curr;
	HandleNode hn2(&curr);
	while(true){		
		pred = head;
		curr = pred->next;
		while(curr->value <  value){
			pred = curr;
			curr = curr->next;
		}
		pred->lock();
		curr->lock();
	
		if(validate(pred,curr)){
			if(curr->value == value){
			//	*re = 1;
			//	break;
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

bool OptimisticList::validate(Node* pred,Node* curr)
{
	Node* node = head;
	
	while(node!=pred&&node!=tail){
		node = node->next;
	}
	return node == pred && node->next == curr;
	

}

string OptimisticList::toString()
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

string OptimisticList::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
