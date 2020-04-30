#include <stdlib.h>
#include "azalea/syscall.h"

_Noreturn void _Exit(int ec)
{
	syscall_exit_process(ec);
	for (;;) syscall_exit_process(ec);
}
