#include <stdlib.h>
#include <stdint.h>
#include "libc.h"

int __cxa_atexit(void (*func)(void *), void *arg, void *dso)
{
	// Do nothing, the kernel never 'exits'
	return 0;
}

int atexit(void (*func)(void))
{
	// Do nothing, the kernel never 'exits'
	return 0;
}
