#include <termios.h>
#include <sys/ioctl.h>

int tcflush(int fd, int queue)
{
	/* Has no meaning in Azalea */
	return 0;
}
