#ifndef ATOMICSTAMPEDREFERENCE_H_
#define ATOMICSTAMPEDREFERENCE_H_

#include "AtomicReference.h"

template <class T>
class AtomicStampedReference{
private:
	template <class V>
	class ReferenceIntegerPair{
	public:
		V* reference;
		int integer;
		ReferenceIntegerPair(V* r,int i){
			reference = r;
			integer = i;
		}
	};
	AtomicReference<ReferenceIntegerPair<T> >* atomicRef;
public:
	AtomicStampedReference(T* initialRef,int initialStamp);
	T* getReference();
	int getStamp();
	T* get(int& stampHolder);
	bool compareAndSet(T* expectedReference,T* newReference,
				int expectedStamp,int newStamp);
	void set(T* newReference,int newStamp);
	bool attemptStamp(T* expectedReference,int newStamp);

};

template <class T>
AtomicStampedReference<T>::AtomicStampedReference(T* initialRef,int initialStamp)
{
	atomicRef = new AtomicReference<ReferenceIntegerPair<T> >(new ReferenceIntegerPair<T>(initialRef,initialStamp));
}

template <class T>
T* AtomicStampedReference<T>::getReference()
{
	return atomicRef->get()->reference;
}

template <class T>
int AtomicStampedReference<T>::getStamp()
{
	return atomicRef->get()->integer;
}

template <class T>
T* AtomicStampedReference<T>::get(int& stampHolder)
{
	ReferenceIntegerPair<T>* p = atomicRef->get();
	stampHolder = p->integer;
	return p->reference;
}

template <class T>
void AtomicStampedReference<T>::set(T* newReference,int newStamp)
{
	ReferenceIntegerPair<T>* current = atomicRef->get();
	if(newReference != current->reference || newStamp != current->integer)
		atomicRef->set(new ReferenceIntegerPair<T>(newReference,newStamp));
}

template <class T>
bool AtomicStampedReference<T>::attemptStamp(T* expectedReference,int newStamp)
{
	ReferenceIntegerPair<T>* current = atomicRef->get();
	return expectedReference == current->reference&&
		(newStamp == current->integer||
		atomicRef->compareAndSet(current,
					new ReferenceIntegerPair<T>(expectedReference,newStamp)));
}

template <class T>
bool AtomicStampedReference<T>::compareAndSet(T* expectedReference,
					T* newReference,
					int expectedStamp,
					int newStamp)
{
	ReferenceIntegerPair<T>* current = atomicRef->get();
	return expectedReference == current->reference&&
		expectedStamp == current->integer&&
		((newReference == current->reference &&
		newStamp == current->integer)||
		atomicRef->compareAndSet(current,
				new ReferenceIntegerPair<T>(newReference,newStamp)));
}
#endif
