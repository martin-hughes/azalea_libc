#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "libc.h"

#include <azalea/syscall.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	struct object_properties props;
	ERR_CODE ec;
	uint64_t size;
	GEN_HANDLE h;

	if (!buf)
	{
		errno = EFAULT;
		return -1;
	}

	buf->st_atim.tv_sec = 0;
	buf->st_atim.tv_nsec = 0;
	buf->st_ctim.tv_sec = 0;
	buf->st_ctim.tv_nsec = 0;
	buf->st_dev = 0;
	buf->st_gid = 0;
	buf->st_ino = 0;
	buf->st_mode = 0;
	buf->st_mtime = 0;
	buf->st_nlink = 0;
	buf->st_rdev = 0;
	buf->st_size = 0;
	buf->st_uid = 0;
	buf->st_blksize = 0;
	buf->st_blocks = 0;

	ec = az_get_object_properties(0, path, strlen(path), &props);
	if (ec == NOT_FOUND)
	{
		errno = ENOENT;
		return -1;
	}
	else if (ec != NO_ERROR)
	{
		errno = EFAULT;
		return -1;
	}

	if (props.is_file)
	{
		/* Don't worry too much about errors here - if an error occurs getting the file size, just return 0. */
		az_open_handle(path, strlen(path), &h, 0);
		ec = az_get_handle_data_len(h, &size);
		if (ec == NO_ERROR)
		{
			buf->st_size = (off_t)size;
		}
		az_close_handle(h);
		buf->st_mode = S_IFREG | 0777;
	}
	else if (!props.is_leaf)
	{
		buf->st_mode = S_IFDIR | 0777;
	}

	return 0;
}

LFS64(stat);
