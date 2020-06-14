#include <poll.h>
#include <time.h>
#include <signal.h>
#include "libc.h"
#include <errno.h>
#include <azalea/syscall.h>

/* This function is still badly broken, but it's enough to support ncurses. */
int poll(struct pollfd *fds, nfds_t n, int timeout)
{
	ERR_CODE ec;

	/* Azalea can only cope with waiting for one object at a time */
	if (n != 1)
	{
		errno = ENOSYS;
		return -1;
	}
	if (!fds)
	{
		errno = EINVAL;
		return -1;
	}

	/* Nothing to wait for. */
	if ((fds[0].fd < 0) ||
			(az_wait_for_object(fds[0].fd, timeout) == TIMED_OUT))
	{
		return 0;
	}

	/* In that case, assume that everything is OK. */
	fds[0].revents = POLLIN;
	return 1;
}
