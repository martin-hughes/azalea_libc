#include "stdio_impl.h"
#include <sys/uio.h>

#include <azalea/syscall.h>

size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
	struct iovec iovs[2] = {
		{ .iov_base = f->wbase, .iov_len = f->wpos-f->wbase },
		{ .iov_base = (void *)buf, .iov_len = len }
	};
	struct iovec *iov = iovs;
	size_t rem = iov[0].iov_len + iov[1].iov_len;
	int iovcnt = 2;
	ssize_t cnt, cnt_0;
	ERR_CODE ec;


	for (;;) {

		cnt = 0;

		for (int i = 0; i < iovcnt; i++)
		{
			if ((iov[i].iov_base != NULL) && (iov[i].iov_len != 0))
			{
				ec = syscall_write_handle(f->fd,
																	f->seek_pos,
																	iov[i].iov_len,
																	iov[i].iov_base,
																	iov[i].iov_len,
																	(unsigned long *)&cnt_0);

				if (ec != NO_ERROR)
				{
					f->flags |= F_ERR;
					return cnt;
				}

				f->seek_pos += cnt_0;
				cnt += cnt_0;
			}
		}

		if (cnt == rem) {
			f->wend = f->buf + f->buf_size;
			f->wpos = f->wbase = f->buf;
			return len;
		}
		if (cnt < 0) {
			f->wpos = f->wbase = f->wend = 0;
			f->flags |= F_ERR;
			return iovcnt == 2 ? 0 : len-iov[0].iov_len;
		}
		rem -= cnt;
		if (cnt > iov[0].iov_len) {
			cnt -= iov[0].iov_len;
			iov++; iovcnt--;
		}
		iov[0].iov_base = (char *)iov[0].iov_base + cnt;
		iov[0].iov_len -= cnt;
	}
}
