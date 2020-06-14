#include <unistd.h>
#include <assert.h>
#include "libc.h"

#include <azalea/syscall.h>

off_t lseek(int fd, off_t offset, int whence)
{
	ERR_CODE ec;
	unsigned long file_len;
	SEEK_OFFSET off_d;
	uint64_t new_off;

	switch(whence)
	{
	case SEEK_SET:
		off_d = FROM_START;
		break;

	case SEEK_CUR:
		off_d = FROM_CUR;
		break;

	case SEEK_END:
		off_d = FROM_END;
		break;

	default:
		break;
	}

	az_seek_handle(fd, offset, off_d, &new_off);

	return new_off;
}

LFS64(lseek);
