#ifndef COARSELIST_H_
#define COARSELIST_H_

#include <string>
#include <pthread.h>
#include <sstream>
#include <iostream>
#include "MyLock.h"
#include "HandleLock.h"
#define MAX_VALUE 2000
#define MIN_VALUE -2

using namespace std;

class CoarseList{

private:
	class Node{
	public:
		int value;
		Node* next;
		Node()
		{	
			value = -1;
			next = NULL;
		}	
		Node(int m_value)
		{
			value = m_value;
			next = NULL;
		}

	};
	Node* head;
	Node* tail;
//	pthread_mutex_t lock;	
	MyLock* lock;
	
	string trans(int ori);

public:
	CoarseList();

	bool add(int value);
	bool remove(int value);	
	bool contains(int value);
	string toString();
	
};


#endif
