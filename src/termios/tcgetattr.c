#include <termios.h>
#include <azalea/azalea.h>
#include <errno.h>
#include <string.h>

#ifndef NULL
#define NULL (void *)(0)
#endif

#define SET_FLAG_IF(cond, flag, store) if ( cond ) { tio-> store |= flag; }

int tcgetattr(int fd, struct termios *tio)
{
  struct terminal_opts azalea_tco;
	struct ssm_output output_opts;

	if (!tio)
	{
		errno = EFAULT;
		return -1;
	}

	output_opts.completion_semaphore = 0;
	output_opts.output_buffer = (char *)(&azalea_tco);
	output_opts.output_buffer_len = sizeof(azalea_tco);

	if (syscall_send_message(fd, SM_GET_OPTIONS, 0, NULL, &output_opts) != NO_ERROR)
	{
		errno = EFAULT;
		return -1;
	}

	memset(tio->c_cc, 0, sizeof(tio->c_cc));
	tio->c_cflag = 0;
	tio->c_iflag = 0;
	tio->c_lflag = 0;
	tio->c_line = 0;
	tio->c_oflag = 0;

	SET_FLAG_IF(azalea_tco.line_discipline, ICANON, c_lflag);

	SET_FLAG_IF(azalea_tco.input_return_is_newline, ICRNL, c_iflag);

	SET_FLAG_IF(azalea_tco.output_newline == CR_TO_CRLF, OCRNL, c_oflag);
	SET_FLAG_IF((azalea_tco.output_newline == LF_TO_CRLF) || (azalea_tco.output_newline == CR_TO_CRLF), ONLCR, c_oflag);

	/*
	This field affects the special characters - we don't do this yet.
	SET_FLAG_IF(azalea_tco.char_7f_is_backspace, ..., ...);*/

	return 0;
}
