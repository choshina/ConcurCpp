#ifndef BACKOFF_H_
#define BACKOFF_H_

#include <ctime>
#include <cstdlib>
#include <unistd.h>
//#include <syswait.h>
using namespace std;

class Backoff{
private:
	int minDelay;
	int maxDelay;
	int limit;
public:
	Backoff(int min,int max);
	void backoff();
};


#endif
