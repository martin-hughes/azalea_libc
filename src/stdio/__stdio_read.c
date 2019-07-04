#include "stdio_impl.h"
#include <sys/uio.h>

#include <azalea/syscall.h>

size_t __stdio_read(FILE *f, unsigned char *buf, size_t len)
{
	struct iovec iov[2] = {
		{ .iov_base = buf, .iov_len = len - !!f->buf_size },
		{ .iov_base = f->buf, .iov_len = f->buf_size }
	};
	ssize_t cnt = 0;
	ssize_t cnt_0 = 0;
	ERR_CODE ec = NO_ERROR;

	/*cnt = iov[0].iov_len ? syscall(SYS_readv, f->fd, iov, 2)
		: syscall(SYS_read, f->fd, iov[1].iov_base, iov[1].iov_len);*/

	if (iov[0].iov_len)
	{
		ec = syscall_read_handle(f->fd, 0, len, iov[0].iov_base, iov[0].iov_len, (unsigned long *)&cnt_0);
	}

	/*
	 * Ignoring the INVALID_PARAM response code here seems a bit odd, but most times INVALID_PARAM is used are times the
	 * Linux equivalent system call (read()) would not trigger an error, so we shouldn't either.
	 */
	if ((ec == NO_ERROR) || (ec == INVALID_PARAM))
	{
		ec = syscall_read_handle(f->fd, 0, len, iov[1].iov_base, iov[1].iov_len, (unsigned long *)&cnt);
		cnt += cnt_0;
	}

	if ((ec != NO_ERROR) && (ec != INVALID_PARAM))
	{
		f->flags = F_ERR;
		cnt = 0;
	}
	else if (cnt <= 0) {
		f->flags |= cnt ? F_ERR : F_EOF;
		return 0;
	}
	if (cnt <= iov[0].iov_len) return cnt;
	cnt -= iov[0].iov_len;
	f->rpos = f->buf;
	f->rend = f->buf + cnt;
	if (f->buf_size) buf[len-1] = *f->rpos++;
	return len;
}
