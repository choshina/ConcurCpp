#ifndef ATOMICREFERENCE_H_
#define ATOMICREFERENCE_H_

#include <iostream>
using namespace std;

#define MP 4
#define LOCK_IF_MP(mp) "cmp $0, "#mp ";je 1f;lock;1:"

template <class T>
class AtomicReference{
private:
	T* value;
	long cmpxchg(long exchange_value,volatile long* dest,long compare_value)
	{
		int mp = MP;
		__asm__ volatile(
			LOCK_IF_MP(%4) "cmpxchgq %1,(%3)"
			:"=a" (exchange_value)
			:"r" (exchange_value),"a"(compare_value),"r"(dest),"r"(mp)
			:"cc","memory"
		);
		return exchange_value;
	}
public:
	AtomicReference();
	AtomicReference(T* initialValue);
	T* get();
	void set(T* newValue);
	T* getAndSet(T* newValue);
	bool compareAndSet(T* expect,T* update);
};

template <class T>
AtomicReference<T>::AtomicReference()
{

}

template <class T>
AtomicReference<T>::AtomicReference(T* initialValue)
{
	value = initialValue;
}

template <class T>
T* AtomicReference<T>::get()
{
	return value;
}

template <class T>
void AtomicReference<T>::set(T* newValue)
{
	value = newValue;
}

template <class T>
T* AtomicReference<T>::getAndSet(T* newValue)
{
	while(true){
		T* x = get();
		if(compareAndSet(x,newValue))
			return x;
	}
}

template <class T>
bool AtomicReference<T>::compareAndSet(T* expect,T* update)
{
	return cmpxchg((long)update,(long*)&value,(long)expect) == (long)expect;
}
#endif

