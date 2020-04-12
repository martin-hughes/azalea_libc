#include <errno.h>
#include "pthread_impl.h"

/* Use this value in the kernel, where pthreads are not supported */
int errno_one_thread;

/* Use pthreads to provide errno outside of the kernel. This choice is made in the errno header file */
int *__errno_location(void)
{
	return &__pthread_self()->errno_val;
}

