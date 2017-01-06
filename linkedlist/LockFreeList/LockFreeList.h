#ifndef LOCKFREELIST_H_
#define LOCKFREELIST_H_

#include "AtomicMarkableReference.h"
#include <string>
#include <sstream>

using namespace std;
#define MAX_VALUE 2000
#define MIN_VALUE -2

class LockFreeList{
private:
	class Node{
	public:
		int value;
		AtomicMarkableReference<Node>* next;
		Node(int m_item){
			value = m_item;
			next = new AtomicMarkableReference<Node>(NULL,false);
		}
	
	};
	class WindowGet{
	public:
		Node* pred;
		Node* curr;
		WindowGet(Node* m_pred,Node* m_curr){
			pred = m_pred;
			curr = m_curr;
		}
	};
	Node* head;
	Node* tail;
	string trans(int ori);
public:
	LockFreeList();
	bool add(int value);
	bool remove(int value);
	bool contains(int value);
	WindowGet* find(Node* t_head, int value);
	string toString();
};


#endif
