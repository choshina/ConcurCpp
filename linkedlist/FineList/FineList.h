#ifndef FINELIST_H_
#define FINELIST_H_

#include <iostream>
#include <string>
#include <pthread.h>
#include <sstream>
//#include "HandleNode.h"
#define MIN_VALUE -2
#define MAX_VALUE 2000

using namespace std;

class FineList{
private:
	class Node{
	public:
		int value;
		Node* next;
		pthread_mutex_t mutex;
		Node()
		{
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
	Node* head;
	Node* tail;
	string trans(int ori);
	
public:
	FineList();
	
	bool add(int value);
	bool remove(int value);
	bool contains(int value);
	string toString();
};

#endif
