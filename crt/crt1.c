#include <features.h>

#define START "_start"

#include "crt_arch.h"

int main();
void _init() __attribute__((weak));
void _fini() __attribute__((weak));
_Noreturn int __libc_start_main(int (*)(), int, char **, char **, void (*)(), void(*)(), void(*)());

void _start_c(unsigned long argc, void **argv, void **envp)
{
	__libc_start_main(main, argc, argv, envp, _init, _fini, 0);
}
