#include <azalea/syscall.h>
#include <sched.h>

int sched_yield()
{
	syscall_yield();
	return 0;
}
