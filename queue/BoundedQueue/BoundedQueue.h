#ifndef BOUNDEDQUEUE_H_
#define BOUNDEDQUEUE_H_

#include <pthread.h>
#include "AtomicInteger.h"
#include <string>
#include <sstream>
using namespace std;

class BoundedQueue{
private:
	class Node{
	public:
		int value;
		Node* next;
		Node(int x){
			value = x;
			next = NULL;
		}
	};
	pthread_mutex_t enqLock;
	pthread_mutex_t deqLock;
	pthread_cond_t notEmptyCond;
	pthread_cond_t notFullCond;
	AtomicInteger* size;
	Node* head;
	Node* tail;
	int capacity;
	string trans(int ori);
	
public:
	BoundedQueue(int length);
	void enq(int x);
	int deq();
	string toString();
};

#endif
