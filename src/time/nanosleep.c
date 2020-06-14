#include <azalea/syscall.h>
#include <time.h>
#include "libc.h"

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	uint64_t ns = req->tv_nsec + (req->tv_sec * 1000000000ULL);

	az_sleep_thread(ns);
	rem->tv_sec = 0;
	rem->tv_nsec = 0;
	return 0 ;
}
