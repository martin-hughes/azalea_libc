#include <signal.h>
#include "libc.h"
#include <azalea/syscall.h>

int __sigaction(int, const struct sigaction *, struct sigaction *);

void (*signal(int sig, void (*func)(int)))(int)
{
	/* Azalea doesn't presently support signal handlers, but it will do in future */
	syscall_debug_output("WARNING: signal() called\n", 25);
/*	struct sigaction sa_old, sa = { .sa_handler = func, .sa_flags = SA_RESTART };
	if (__sigaction(sig, &sa, &sa_old) < 0)
		return SIG_ERR;
	return sa_old.sa_handler;*/
	return 0;
}

weak_alias(signal, bsd_signal);
weak_alias(signal, __sysv_signal);
