#include <azalea/syscall.h>
#include <sched.h>

int sched_yield()
{
	az_yield();
	return 0;
}
