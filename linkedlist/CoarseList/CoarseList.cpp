#include "CoarseList.h"


CoarseList::CoarseList()
{
	head = new Node(MIN_VALUE);
	tail = new Node(MAX_VALUE);
	head->next = tail;
//	pthread_mutex_init(&lock,NULL);
	lock = new MyLock();
}

bool CoarseList::add(int value)
{

//	pthread_mutex_lock(&lock);
//	lock->lock();
	HandleLock hl(lock);
//	cout<<"add"<<value<<endl;
	
	Node* pred = head;
	Node* curr = head->next;
	
	while(curr->value < value){
		pred = curr;
		curr = curr->next;
	}
	
	if(curr->value == value){
//		*re = 0;
		return false;
		
	}else{
		Node* newNode = new Node(value);
		pred->next = newNode;
		newNode->next = curr;
//		*re = 1;
		return true;
	}
//	pthread_mutex_unlock(&lock);
}


bool CoarseList::remove(int value)
{
//	pthread_mutex_lock(&lock);
	HandleLock hl(lock);
//	cout<<"remove"<<value<<endl;

	Node* pred = head;
	Node* curr = head->next;
	
	while(curr->value < value){
		pred = curr;
		curr = curr->next;
	}
	if(curr->value == value){
		pred->next = curr->next;
//		*re = 1;
		return true;
		
		
	}else{
//		*re = 0;
		return false;
		
		
	}
//	pthread_mutex_unlock(&lock);
}


bool CoarseList::contains(int value)
{
//	pthread_mutex_lock(&lock);
	HandleLock hl(lock);
//	cout<<"contains"<<value<<endl;

	Node* curr = head;
	while(curr->value < value){
		curr = curr->next;
	}
	if(curr->value == value){

	//	*re = 1;
		return true;
	}else{
//		*re = 0;
		return false;
	}
	
//	pthread_mutex_unlock(&lock);
	
}

string CoarseList::toString()
{
	Node* curr = head->next;
	string s = "";
	
	while(curr->value != MAX_VALUE){
		
		s = s + trans(curr->value);
		s = s + '\n';	
		curr = curr->next;
	}
	return s;
}

string CoarseList::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
