#include "Backoff.h"

Backoff::Backoff(int min,int max)
{
	minDelay = min;
	maxDelay = max;
	limit = minDelay;
	srand((unsigned)time(NULL));
}

void Backoff::backoff()
{
	int delay = rand()%limit;
	limit = maxDelay<(limit*2)?maxDelay:2*limit;
	usleep(delay*100);
}

