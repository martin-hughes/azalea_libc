#include "stdio_impl.h"

#include <azalea/syscall.h>

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int __stdio_close(FILE *f)
{
	ERR_CODE ec;
	ec = syscall_close_handle(__aio_close(f->fd));

	return ec == NO_ERROR ? 0 : -1;
}
