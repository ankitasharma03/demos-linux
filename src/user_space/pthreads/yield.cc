#include <pthread.h> // for pthread_yield(3), pthread_create(3), pthread_join(3)
#include <sched.h> // for sched_yield(2)
#include <stdio.h> // for fprintf(3)
#include <stdlib.h> // for exit(3)
#include <unistd.h> // for sleep(3)

#include "us_helper.hh"

/*
 *      This is a demo for the sched_yield(2) or for pthread_yield(3) which are
 *      in effect the same. The difference between these two functions is that
 *      sched_yield could be used and should be used in a multi process context
 *      while pthread_yield is more appropriate in a multi threaded context.
 *
 *      The idea of this demo is to show how two threads yield one to the other
 *      using this API and no other synchronization mechanism except an atomic
 *      variable. Ofcourse they spin a lot in this example.
 *
 *      If you run this demo on a single CPU machine then you will see that
 *      the output that you get from the two threads is interwoven which means
 *      that they yield one to the other.
 *      Ofcourse, this is not strictly a proof that this works since even on a single
 *      CPU machine with heavy load it could be that not even the single TRACE executing
 *      could fit in a time slot. But you get the idea.
 *      If you look at the first runs you would see that one of these threads gets a lot
 *      of the CPU. This is because it takes time to create the other thread in the
 *      operating system and it seems that yield does not always guarantee that the other
 *      thread wins.
 *      There is a barrier here also used to jump start the threads at exactly the same
 *      time but strictly speaking it is not required for this demo.
 *
 *                      Mark Veltzer
 *
 * EXTRA_LIBS=-lpthread
 */

//#define DO_BARRIER
//#define DO_ONEYIELD

#ifdef DO_BARRIER
pthread_barrier_t barrier;
#endif // DO_BARRIER
int counter=0;
bool ended=false;

void *worker(void *p) {
#ifdef DO_BARRIER
	// do not CHECK_ZERO on the line below since pthread_barrier_wait DOES NOT
	// always return zero (actually, it always returns something else than zero
	// to one of the threads (like a leader...)
	pthread_barrier_wait(&barrier);
#endif // DO_BARRIER
	int prev=0;
	bool first=true;
	for(unsigned int i=0;i<10;i++) {
	//while (true) {
		//TRACE("im here");
		int cur= __sync_add_and_fetch(&counter, 1);
		if(!first) {
			if(cur!=prev+2) {
				fprintf(stderr,"error, cur %d is wrong, prev is %d\n",cur,prev);
				exit(1);
			}
		} else {
			first=false;
		}
		prev=cur;
		TRACE("counter is %d, cur is %d",counter,cur);
#ifndef DO_ONEYIELD
		while(counter==cur && !ended) {
			CHECK_ZERO(sched_yield());
		}
#else // DO_ONEYIELD
		CHECK_ZERO(pthread_yield());
#endif // DO_ONEYIELD
	}
	ended=true;
	TRACE("ending");
	return(NULL);
}

int main(int argc, char **argv, char **envp) {
	TRACE("start");
	const unsigned int num = 2;
	pthread_t threads[num];
#ifdef DO_BARRIER
	CHECK_ZERO(pthread_barrier_init(&barrier,NULL,num));
#endif // DO_BARRIER
	for (unsigned int i = 0; i < num; i++) {
		CHECK_ZERO(pthread_create(threads + i, NULL, worker, NULL));
	}
	//sleep(1);
	TRACE("created threads, now joining...");
	for (unsigned int i = 0; i < num; i++) {
		CHECK_ZERO(pthread_join(threads[i],NULL));
	}
	TRACE("end");
	return(0);
}