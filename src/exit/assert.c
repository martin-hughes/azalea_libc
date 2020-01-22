#include <stdio.h>
#include <stdlib.h>
#include <azalea/syscall.h>

_Noreturn void __assert_fail(const char *expr, const char *file, int line, const char *func)
{
	fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
	fflush(NULL);
	syscall_debug_output("WARNING: abort() called\n", 24);
	abort();
}
