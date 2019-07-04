#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include "libc.h"

#include <stdio.h>

#include <azalea/syscall.h>

int fstat(int fd, struct stat *st)
{
	ERR_CODE ec;
	struct object_properties props;
	uint64_t size;
	int rv = 0;

	st->st_atim.tv_sec = 0;
	st->st_atim.tv_nsec = 0;
	st->st_ctim.tv_sec = 0;
	st->st_ctim.tv_nsec = 0;
	st->st_dev = 0;
	st->st_gid = 0;
	st->st_ino = 0;
	st->st_mode = 0;
	st->st_mtime = 0;
	st->st_nlink = 0;
	st->st_rdev = 0;
	st->st_size = 0;
	st->st_uid = 0;
	st->st_blksize = 0;
	st->st_blocks = 0;

	ec = syscall_get_object_properties(fd, NULL, 0, &props);
	if (ec == NOT_FOUND)
	{
		errno = ENOENT;
		rv = -1;
	}
	else if (ec != NO_ERROR)
	{
		errno = EFAULT;
		rv = -1;
	}

	ec = syscall_get_handle_data_len(fd, &size);
	if (ec == NO_ERROR)
	{
		/* printf("Got file size: %ll\n", size); */
		st->st_size = size;
	}
	else
	{
		/* printf("Failed to get file size\n"); */
	}

	return rv;
}

LFS64(fstat);
