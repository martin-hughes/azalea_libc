#include "stdio_impl.h"

#include <azalea/syscall.h>

off_t __stdio_seek(FILE *f, off_t off, int whence)
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
		f->flags |= F_ERR;
		break;
	}

	if ((f->flags & F_ERR) == 0)
	{
		if (syscall_seek_handle(f->fd, off, off_d, &new_off) != NO_ERROR)
		{
			f->flags |= F_ERR;
		}
	}

	return new_off;
}
