#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include "libc.h"

#include <azalea/syscall.h>

#include <stdio.h>

/* Known defects:
 * - Most of the O_* flags will not work as expected...
 * - What do we do if we try to create a file and it can't have its length set to zero?
 */

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;
	ERR_CODE ec;
	GEN_HANDLE h;
	int fd_num = 0;
	uint32_t syscall_flags = 0;
	uint64_t file_len;

	/*printf("Opening\n");*/

	if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	if (flags & O_CREAT)
	{
		syscall_flags = H_CREATE_IF_NEW;
	}
	ec = az_open_handle(filename, strlen(filename), &h, syscall_flags);

	if (ec == NO_ERROR)
	{
		if (flags & O_CREAT)
		{
			/* O_CREAT basically requests the file length be set to zero. What should we do if this fails? */
			az_set_handle_data_len(h, 0);
		}
		else if (flags & O_APPEND)
		{
			ec = az_get_handle_data_len(h, &file_len);
			az_seek_handle(h, file_len, FROM_START, NULL);
		}
	}
	else
	{
		h = 0;
	}

	return h;
}

LFS64(open);
