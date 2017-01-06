#include "AtomicReference.h"
#include <iostream>
#include "Tint.h"
using namespace std;

int main()
{
	Tint a(1);
	AtomicReference<Tint>* ai = new AtomicReference<Tint>(&a);
	cout<<ai->get()->get();

	Tint b(6);
	AtomicReference<Tint>* ai2 = ai;
	AtomicReference<Tint>* ai3 = new AtomicReference<Tint>(&b);
	if(ai->compareAndSet(&a,&b))
		cout<<ai->get()->get();
}
