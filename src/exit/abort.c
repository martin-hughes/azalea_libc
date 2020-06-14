#include <stdlib.h>
#include <signal.h>
#include "pthread_impl.h"
#include "atomic.h"
#include "azalea/syscall.h"

_Noreturn void abort(void)
{
	a_crash();
	az_exit_process(~0);
	while (1) { az_exit_process(~0); };
}
