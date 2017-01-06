#include "EliminationBackoffStack.h"

EliminationBackoffStack::EliminationBackoffStack()
{
	top = new AtomicReference<Node>(NULL);
	eliminationArray = new EliminationArray();
}

void EliminationBackoffStack::push(int value)
{
	Node* node = new Node(value);
	while(true){
		if(tryPush(node)){
			return;
		}else{
			int* otherValue = eliminationArray->visit(&value);
			if(otherValue == NULL){
				return;
			}
		}
	
	}
}

bool EliminationBackoffStack::tryPush(Node* node)
{
	Node* oldTop = top->get();
	node->next = oldTop;
	return (top->compareAndSet(oldTop,node));
}

int EliminationBackoffStack::pop()
{
	while(true){
		Node* returnNode = tryPop();
		if(returnNode != NULL){
			return returnNode->value;
		}else{

			int* otherValue = eliminationArray->visit(NULL);
			if(otherValue!=NULL){
				return *otherValue;
			}
		}
	}
}

EliminationBackoffStack::Node* EliminationBackoffStack::tryPop()
{
	Node* oldTop = top->get();
	if(oldTop == NULL){
		return NULL;
	}
	Node* newTop = oldTop->next;
	if(top->compareAndSet(oldTop,newTop)){
		return oldTop;
	}else{
		return NULL;
	}
}
