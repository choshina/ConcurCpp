#ifndef CMPXCHG_H_
#define CMPXCHG_H_

#define MP 4
#define LOCK_IF_MP(mp) "cmp $0,"#mp ";je 1f;lock;1:"
//#define LOCK_IF_MP(mp) "cmp $0,mp;je 1f;lock;1:"
//#define LOCK_IF_MP(mp) "cmp $0,%mp"#mp ";je 1f;lock;1:"

int cmpxchg(int exchange_value,volatile int* dest,int compare_value)
{
	int mp = MP;
	__asm__ __volatile__(
		LOCK_IF_MP(%4) "cmpxchgl %1,(%3)"
		:"=a" (exchange_value)
		:"r" (exchange_value),"a"(compare_value), "r"(dest),"r"(mp)
		:"cc","memory"
	);
	return exchange_value;

}

#endif
