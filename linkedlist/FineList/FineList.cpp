#include "FineList.h"
//it is not safe to unlock a before locking b
//because another thread could remove b from the list 
//int the interval between unlocking a and locking b
FineList::FineList()
{
	head = new Node(MIN_VALUE);
	tail = new Node(MAX_VALUE);
	head->next = tail;
	

}

bool FineList::add(int value)
{
	head->lock();
	Node* pred;
	HandleNode hn1(&pred);
	Node* curr;
	HandleNode hn2(&curr);
	pred = head;
	curr = pred->next;
	curr->lock();
	while(curr->value < value){
		pred->unlock();
		pred = curr;
		curr = curr->next;
		curr -> lock();
	}
	if(curr->value == value){
	//	*re = 0;
		return false;
	}else{

		Node* node = new Node(value);
		node -> next = curr;
		pred -> next = node;
	//	*re = 1;
		return true;
		
	}
//	cout<<"add"<<value<<endl;
//	curr->unlock();
//	pred->unlock();
}

bool FineList::remove(int value)
{
	Node* pred;
	HandleNode hn1(&pred);
	Node* curr;
	HandleNode hn2(&curr);
	head->lock();
	
	pred = head;
	
	curr = pred ->next;
	curr ->lock();
	while(curr->value < value){
		pred->unlock();
		pred = curr;
		curr = curr ->next;
		curr ->lock();
	}
	if(curr->value != value){
//		*re = 0;
		return false;
	}else{
		pred->next = curr->next;
	//	*re = 1;
		return true;
	}
//	cout<<"remove"<<value<<endl;
//	curr->unlock();
//	pred->unlock();
}

bool FineList::contains(int value)
{
	Node* curr;
	Node* pred;
	HandleNode hn1(&curr);
	HandleNode hn2(&pred);
	
	head->lock();
	pred = head;
	curr = head->next;
	curr->lock();
	
	while(curr->value <  value){
		pred->unlock();
		pred = curr;
		curr = curr->next;
		curr->lock();
	} 
	if(curr->value == value){
//		*re = 1;
		return true;
	}else{
	//	*re = 0;
		return false;
	}
//	cout<<"contains"<<value<<endl;
//	curr->unlock();
//	pred->unlock();
	
}

string FineList::toString()
{
	string s = "";
	Node* curr = head->next;
	while(curr->value!=MAX_VALUE){
		s = s + trans(curr->value);
		s = s + '\n';
		curr = curr->next;
	}
	return s;

}

string FineList::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
