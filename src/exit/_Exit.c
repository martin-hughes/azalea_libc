#include <stdlib.h>
#include "azalea/syscall.h"

_Noreturn void _Exit(int ec)
{
	syscall_exit_process();
	for (;;) syscall_exit_process();
}
