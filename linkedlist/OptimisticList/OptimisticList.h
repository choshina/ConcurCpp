#ifndef OPTIMISTIC_H_
#define OPTIMISTIC_H_

#include <iostream>
#include <sstream>
#include <string>
#include <pthread.h>
#define MIN_VALUE -2
#define MAX_VALUE 2000

using namespace std;

class OptimisticList{
private:
	class Node{
	public:
		int value;
		Node* next;
		pthread_mutex_t mutex;
		Node(){
			value = -1;
			next = NULL;
			pthread_mutex_init(&mutex,NULL);
		}
		Node(int m_value)
		{
			value = m_value;
			next = NULL;
			pthread_mutex_init(&mutex,NULL);
		}
		void lock()
		{
			pthread_mutex_lock(&mutex);
		}
		void unlock()
		{
			pthread_mutex_unlock(&mutex);
		}
	};
	class HandleNode{
	private:
		Node** node;
	public:
		HandleNode(Node** n){node = n;}
		~HandleNode(){(*node)->unlock();}
	};
	bool validate(Node* pred,Node* curr);
	Node* head;
	Node* tail;
	string trans(int ori);
public:
	OptimisticList();	
	bool add(int value);
	bool remove(int value);
	bool contains(int value);
	string toString();
};

#endif
