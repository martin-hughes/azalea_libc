#include <stdlib.h>
#include "azalea/syscall.h"

_Noreturn void _Exit(int ec)
{
	az_exit_process(ec);
	for (;;) az_exit_process(ec);
}
