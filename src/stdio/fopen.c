#include "stdio_impl.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <azalea/syscall.h>

FILE *fopen(const char *restrict filename, const char *restrict mode)
{
	FILE *f;
	ERR_CODE ec;
	GEN_HANDLE fd;
	int flags;

	/* Check for valid initial mode character */
	if (!strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

	/* Compute the flags to pass to open() */
	flags = __fmodeflags(mode);

	/* We don't currently support CLOEXEC */
	if (flags & O_CLOEXEC)
	{
		return 0;
	}

	ec = syscall_open_handle(filename, strlen(filename), &fd);
	if (ec != NO_ERROR)
	{
		return 0;
	}

	f = __fdopen(fd, mode);
	if (f)
	{
		 return f;
	}
	else
	{
		syscall_close_handle(fd);
	}

	return 0;
}

LFS64(fopen);
