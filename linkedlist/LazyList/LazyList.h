#ifndef LAZYLIST_H_
#define LAZYLIST_H_

#include <iostream>
#include <string>
#include <sstream>
#include <pthread.h>

#define MIN_VALUE -2
#define MAX_VALUE 2000

using namespace std;



class LazyList{
private:
	class Node{
	public:
		int value;
		Node* next;
		pthread_mutex_t mutex;
		bool mark;
		Node(){
			value = -1;
			next = NULL;
			pthread_mutex_init(&mutex,NULL);
			mark = false;
		}
		Node(int m_value){
			value = m_value;
			next = NULL;
			pthread_mutex_init(&mutex,NULL);
			mark = false;
		}
		void lock(){
			pthread_mutex_lock(&mutex);
		}
		void unlock(){
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
	bool validate(Node* pred,Node* curr);
public:
	LazyList();
	
	bool add(int value);
	bool remove(int value);
	bool contains(int value);	
	string toString();


};

#endif
