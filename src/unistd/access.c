#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <azalea/syscall.h>
#include <errno.h>
#include <string.h>

/* This isn't needed yet, so it isn't implemented. */

int access(const char *filename, int amode)
{
	struct object_properties props;
	ERR_CODE ec;
	uint64_t size;
	GEN_HANDLE h;

	ec = az_get_object_properties(0, filename, strlen(filename), &props);
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

	return 0;
}
