#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <azalea/syscall.h>

int ioctl(int fd, int req, ...)
{
	void *arg;
	va_list ap;
	va_start(ap, req);
	arg = va_arg(ap, void *);
	va_end(ap);

	/* Azalea doesn't presently support the iotcl() call, but will do one day */
	syscall_debug_output("WARNING: ioctl() called\n", 24);
	abort();
	/*return syscall(SYS_ioctl, fd, req, arg);*/
}
