#include "UnboundedQueue.h"

UnboundedQueue::UnboundedQueue()
{
	pthread_mutex_init(&enqLock,NULL);
	pthread_mutex_init(&deqLock,NULL);
	head = new Node(-1);
	tail = head;
//	size = 0;
}

void UnboundedQueue::enq(int x)
{
	pthread_mutex_lock(&enqLock);
	Node* newNode = new Node(x);
	tail->next = newNode;
	tail = newNode;
//	size++;
	pthread_mutex_unlock(&enqLock);
}

int UnboundedQueue::deq()
{
	int result;
	pthread_mutex_lock(&deqLock);
	if(head->next == NULL){
		pthread_mutex_unlock(&deqLock);		
		return -1;
	}
	result = head->next->value;
	head = head->next;
	pthread_mutex_unlock(&deqLock);
	return result;
}

string UnboundedQueue::toString()
{
	Node* curr = head->next;
	string s = "";
	while(curr!=NULL){
		s = s + trans(curr->value);
		curr = curr -> next;
	}	
	return s;
}

string UnboundedQueue::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
