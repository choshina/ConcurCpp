test:test.o AtomicInteger.o
	g++ -o test test.o AtomicInteger.o -pthread
test.o:test.cpp AtomicInteger.h
	g++ -c -g test.cpp 
AtomicInteger.o:AtomicInteger.h AtomicInteger.cpp cmpxchg.h
	g++ -c -g AtomicInteger.cpp cmpxchg.h

