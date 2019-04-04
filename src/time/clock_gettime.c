#include <time.h>
#include <errno.h>
#include <stdint.h>
#include "libc.h"
#include "atomic.h"
#include "time_impl.h"

#include <azalea/syscall.h>

long __syscall_ret(unsigned long r);

#ifdef VDSO_CGT_SYM

void *__vdsosym(const char *, const char *);

static void *volatile vdso_func;

static int cgt_init(clockid_t clk, struct timespec *ts)
{
	void *p = __vdsosym(VDSO_CGT_VER, VDSO_CGT_SYM);
	int (*f)(clockid_t, struct timespec *) =
		(int (*)(clockid_t, struct timespec *))p;
	a_cas_p(&vdso_func, (void *)cgt_init, p);
	return f ? f(clk, ts) : -ENOSYS;
}

static void *volatile vdso_func = (void *)cgt_init;

#endif

int __clock_gettime(clockid_t clk, struct timespec *ts)
{
	int r;
	struct time_expanded t;
	ERR_CODE e;
	struct tm tm;

#ifdef VDSO_CGT_SYM
	int (*f)(clockid_t, struct timespec *) =
		(int (*)(clockid_t, struct timespec *))vdso_func;
	if (f) {
		r = f(clk, ts);
		if (!r) return r;
		if (r == -EINVAL) return __syscall_ret(r);
		/* Fall through on errors other than EINVAL. Some buggy
		 * vdso implementations return ENOSYS for clocks they
		 * can't handle, rather than making the syscall. This
		 * also handles the case where cgt_init fails to find
		 * a vdso function to use. */
	}
#endif

	if (clk != CLOCK_REALTIME)
	{
		/* Azalea doesn't currently support any other clock */
		r = -ENOSYS;
	}
	else
	{
		e = syscall_get_system_clock(&t);
		if (e != NO_ERROR)
		{
			r = -ENOSYS;
		}
		else
		{
			/* This is all a bit convoluted, because musl expects a Linux format time, so we convert from our perfectly good
			 * time specification into the Linux one, for it to probably later be converted back to something similar to the
			 * kernel format... */
			ts->tv_nsec = t.nanoseconds;
			tm.tm_year = t.year;
			tm.tm_mon = t.month;
			tm.tm_mday = t.day;
			tm.tm_hour = t.hours;
			tm.tm_min = t.minutes;
			tm.tm_sec = t.seconds;
			ts->tv_sec = __tm_to_secs(&tm);
			r = 0;
		}
	}

	return __syscall_ret(r);
}

weak_alias(__clock_gettime, clock_gettime);
