#include <unistd.h>
#include "libc.h"
#include <errno.h>

#include <azalea/syscall.h>

ssize_t read(int fd, void *buf, size_t count)
{
	uint64_t br = 0;
	ERR_CODE ec;

	ec = syscall_read_handle(fd,
													 0,
													 count,
													 buf,
													 count,
													 &br);

	if (ec == INVALID_PARAM)
	{
		/*
		 * The system call will return an error for reading outside of the boundary of a file, and various other errors,
		 * but read() should just return 0 for most of them...
		 */
		br = 0;
	}
	else if (ec != NO_ERROR)
	{
		br = -1;
		errno = EINVAL;
	}

	return (ssize_t)br;
}
