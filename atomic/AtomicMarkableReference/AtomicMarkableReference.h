#ifndef ATOMICMARKABLEREFERENCE_H_
#define ATOMICMARKABLEREFERENCE_H_

#include "AtomicReference.h"

template <class T>
class AtomicMarkableReference{
private:
	template <class V>
	class ReferenceBooleanPair{
	public:
		V* reference;
		bool bit;
		ReferenceBooleanPair(V* r,bool i){
			reference = r;
			bit = i;
		}
	};
	AtomicReference<ReferenceBooleanPair<T> >* atomicRef;
public:
	AtomicMarkableReference(T* initialRef,bool initialMark);
	T* getReference();
	bool isMarked();
	T* get(bool& markHolder);
	bool compareAndSet(T* expectedReference,T* newReference,
				bool expectedMark,bool newMark);
	void set(T* newReference,bool newMark);
	bool attemptMark(T* expectedReference,bool newMark);	
};

template <class T>
AtomicMarkableReference<T>::AtomicMarkableReference(T* initialRef,bool initialMark)
{
	atomicRef = new AtomicReference<ReferenceBooleanPair<T> >(new ReferenceBooleanPair<T>(initialRef,initialMark));
}

template <class T>
T* AtomicMarkableReference<T>::getReference()
{
	return atomicRef->get()->reference;
}

template <class T>
bool AtomicMarkableReference<T>::isMarked()
{
	return atomicRef->get()->bit;
}

template <class T>
T* AtomicMarkableReference<T>::get(bool& markHolder)
{
	ReferenceBooleanPair<T>* p = atomicRef->get();
	markHolder= p->bit;
	return p->reference;
}

template <class T>
void AtomicMarkableReference<T>::set(T* newReference,bool newMark)
{
	ReferenceBooleanPair<T>* current = atomicRef->get();
	if(newReference != current->reference || newMark != current->bit)
		atomicRef->set(new ReferenceBooleanPair<T>(newReference,newMark));
}

template <class T>
bool AtomicMarkableReference<T>::compareAndSet(T* expectedReference,
						T* newReference,
						bool expectedMark,
						bool newMark)
{
	ReferenceBooleanPair<T>* current = atomicRef->get();
	return expectedReference == current->reference&&
		expectedMark == current->bit&&
		((newReference == current->reference && newMark == current->bit)||
		atomicRef->compareAndSet(current,new ReferenceBooleanPair<T>(newReference,newMark)));
}

template <class T>
bool AtomicMarkableReference<T>::attemptMark(T* expectedReference,bool newMark)
{
	ReferenceBooleanPair<T>* current = atomicRef->get();
	return expectedReference == current->reference&&
		(newMark == current->bit ||
		atomicRef->compareAndSet(current,
					new ReferenceBooleanPair<T>(
					expectedReference,newMark			
					)));
}

#endif
