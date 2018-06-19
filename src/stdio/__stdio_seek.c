#include "stdio_impl.h"

#include <azalea/syscall.h>

off_t __stdio_seek(FILE *f, off_t off, int whence)
{
	ERR_CODE ec;
	unsigned long file_len;

	switch(whence)
	{
	case SEEK_SET:
		f->seek_pos = off;
		break;

	case SEEK_CUR:
		f->seek_pos += off;
		break;

	case SEEK_END:
		ec = syscall_get_handle_data_len(f->fd, &file_len);
		if (ec == NO_ERROR)
		{
			f->seek_pos = off + file_len;
		}
		else
		{
			f->seek_pos = 0;
			f->flags |= F_ERR;
		}

	default:
		f->seek_pos = 0;
		f->flags |= F_ERR;
		break;
	}

	return f->seek_pos;
}
