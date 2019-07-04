#include <unistd.h>
#include <errno.h>
#include "libc.h"

#include <azalea/syscall.h>

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int close(int fd)
{
	ERR_CODE ec = NO_ERROR;

	ec = syscall_close_handle(fd);

	return ((ec == NO_ERROR) ? 0 : EIO);
}
