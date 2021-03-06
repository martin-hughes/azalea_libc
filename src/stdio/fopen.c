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
	uint32_t kernel_flags = 0;

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

	if (strchr(mode, 'w'))
	{
		kernel_flags = H_CREATE_IF_NEW;
	}

	ec = az_open_handle(filename, strlen(filename), &fd, kernel_flags);
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
		az_close_handle(fd);
	}

	return 0;
}

LFS64(fopen);
