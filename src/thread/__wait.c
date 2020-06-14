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
		az_futex_op(addr, FUTEX_WAKE, val, 0, 0, 0);
	}
	if (waiters) a_dec(waiters);
}
