#include "pthread_impl.h"

#include <azalea/syscall.h>

void __wait(volatile int *addr, volatile int *waiters, int val, int priv)
{
	int spins=100;
	if (priv) priv = FUTEX_PRIVATE;
	while (spins-- && (!waiters || !*waiters)) {
		if (*addr==val) a_spin();
		else return;
	}
	if (waiters) a_inc(waiters);
	while (*addr==val) {
		syscall_futex_wait(addr, val);
	}
	if (waiters) a_dec(waiters);
}
