#include <azalea/azalea.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include "futex.h"
#include "pthread_impl.h"

int __pthread_setcancelstate(int, int *);
int __clock_gettime(clockid_t, struct timespec *);

int __timedwait_cp(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	int r;
	struct timespec to;
	uint64_t ns = 0;

	if (priv) priv = FUTEX_PRIVATE;

	if (at) {
		if (at->tv_nsec >= 1000000000UL) return EINVAL;
		if (__clock_gettime(clk, &to)) return EINVAL;
		to.tv_sec = at->tv_sec - to.tv_sec;
		if ((to.tv_nsec = at->tv_nsec - to.tv_nsec) < 0) {
			to.tv_sec--;
			to.tv_nsec += 1000000000;
		}
		if (to.tv_sec < 0) return ETIMEDOUT;

		ns = to.tv_nsec + to.tv_sec * 1000000000ull;
	}

	r = -az_translate_error_code(syscall_futex_op(addr, FUTEX_WAIT, val, ns, 0, 0));
	if (r != EINTR && r != ETIMEDOUT && r != ECANCELED) r = 0;

	return r;
}

int __timedwait(volatile int *addr, int val,
	clockid_t clk, const struct timespec *at, int priv)
{
	int cs, r;
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	r = __timedwait_cp(addr, val, clk, at, priv);
	__pthread_setcancelstate(cs, 0);
	return r;
}
