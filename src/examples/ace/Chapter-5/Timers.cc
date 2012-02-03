// $Id: Timers.cpp 80826 2008-03-04 14:51:23Z wotte $

/*
 * EXTRA_CMDS=pkg-config --cflags --libs ACE
 */

#include <ace/config-all.h>
#include <ace/OS_main.h>
#include <ace/streams.h>
#include <ace/OS_NS_unistd.h>
#include <ace/OS_NS_time.h>
#include <ace/OS_NS_signal.h>

typedef void (*timerTask_t)(void);

// Listing 1 code/ch07
pid_t timerTask(int initialDelay,
                int interval,
                timerTask_t task) {
	if ((initialDelay < 1) && (interval < 1)) {
		return(-1);
	}

	pid_t pid = ACE_OS::fork();

	if (pid < 0) {
		return(-1);
	}

	if (pid > 0) {
		return(pid);
	}

	if (initialDelay > 0) {
		ACE_OS::sleep(initialDelay);
	}

	if (interval < 1) {
		return(0);
	}

	while (1) {
		(*task)();
		ACE_OS::sleep(interval);
	}

	ACE_NOTREACHED(return 0);
}


// Listing 1

// Listing 2 code/ch07
void foo() {
	time_t now = ACE_OS::time(0);

	cerr << "The time is " << ACE_OS::ctime(&now) << endl;
}


// Listing 2
void programMainLoop(void) {
	ACE_OS::sleep(30);
}


// Listing 3 code/ch07
int ACE_TMAIN(int, ACE_TCHAR *[]) {
	pid_t timerId = timerTask(3, 5, foo);

	programMainLoop();
	ACE_OS::kill(timerId, SIGINT);
	return(0);
}