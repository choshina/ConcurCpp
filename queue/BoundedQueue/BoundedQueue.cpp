#include "BoundedQueue.h"


BoundedQueue::BoundedQueue(int length)
{
	pthread_mutex_init(&enqLock,NULL);
	pthread_mutex_init(&deqLock,NULL);
	pthread_cond_init(&notEmptyCond,NULL);
	pthread_cond_init(&notFullCond,NULL);
	size = new AtomicInteger(length);//空节点的数量
	capacity = length;
	head = new Node(-1);
	tail = head;
}

void BoundedQueue::enq(int x)
{
	bool mustWakeDequeuer = false;
	pthread_mutex_lock(&enqLock);
	while(size->get()==0){
		pthread_cond_wait(&notFullCond,&enqLock);
	}
	Node* newNode = new Node(x);
	tail->next = newNode;
	tail = newNode;
	/////////////////////////
	if(size->getAndDecrement() == capacity)
		mustWakeDequeuer = true;
///////////////////////////////////////
	pthread_mutex_unlock(&enqLock);
	if(mustWakeDequeuer){
		pthread_mutex_lock(&deqLock);
		pthread_cond_broadcast(&notEmptyCond);
		pthread_mutex_unlock(&deqLock);
	}
}

int BoundedQueue::deq()
{
	int result;
	bool mustWakeEnqueuer = false;
	pthread_mutex_lock(&deqLock);
	while(size->get() == capacity){
		pthread_cond_wait(&notEmptyCond,&deqLock);
	}
	result = head->next->value;
	head = head->next;
	if(size -> getAndIncrement() == 0)
		mustWakeEnqueuer = true;
	pthread_mutex_unlock(&deqLock);
	if(mustWakeEnqueuer){
		pthread_mutex_lock(&enqLock);
		pthread_cond_broadcast(&notFullCond);
		pthread_mutex_unlock(&enqLock);
	}
	return result;
}

string BoundedQueue::toString()
{
	Node* curr = head->next;
	int i = capacity;
	string s = "";
	while(curr!=NULL&&i!=0){
		s = s + trans(curr->value);
		i--;
		curr = curr->next;
	}
	return s;
}

string BoundedQueue::trans(int ori)
{
	stringstream ss;
	ss<<ori;
	return ss.str();
}
