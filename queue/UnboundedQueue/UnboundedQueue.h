#ifndef UNBOUNDEDQUEUE_H_
#define UNBOUNDEDQUEUE_H_

#include <pthread.h>
#include <string>
#include <sstream>
using namespace std;


class UnboundedQueue{
private:
	class Node{
	public:
		int value;
		Node* next;
		Node(int m_value){
			value = m_value;
			next = NULL;
		}
	};
	pthread_mutex_t enqLock;
	pthread_mutex_t deqLock;
	Node* head;
	Node* tail;
	int size;
	string trans(int ori);
public:
	UnboundedQueue();
	void enq(int x);
	int deq();
	string toString();
};

#endif
