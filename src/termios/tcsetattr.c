#include <termios.h>
#include <errno.h>
#include <azalea/azalea.h>
#include <string.h>

#ifndef NULL
#define NULL (void *)(0)
#endif

/* act is ignored for now */
int tcsetattr(int fd, int act, const struct termios *tio)
{
  struct terminal_opts azalea_tco;

	if (tio == NULL)
	{
		errno = EFAULT;
		return -1;
	}

	memset(&azalea_tco, 0, sizeof(azalea_tco));

	if ((tio->c_lflag & ICANON) != 0)
	{
		azalea_tco.line_discipline = true;
	}

	if (((tio->c_oflag & OCRNL) != 0) && ((tio->c_oflag & ONLCR) != 0))
	{
		azalea_tco.output_newline = CR_TO_CRLF;
	}
	else if ((tio->c_oflag & ONLCR) != 0)
	{
		azalea_tco.output_newline = LF_TO_CRLF;
	}
	else
	{
		azalea_tco.output_newline = NO_CHANGE;
	}

	if ((tio->c_iflag & ICRNL) != 0)
	{
		azalea_tco.input_return_is_newline = true;
	}

	if ((tio->c_iflag & INLCR) != 0)
	{
		azalea_tco.input_newline_is_return = true;
	}

	if (az_send_message(fd, SM_SET_OPTIONS, sizeof(azalea_tco), (char *)(&azalea_tco), NULL) != NO_ERROR)
	{
		errno = EFAULT;
		return -1;
	}

	return 0;
}
