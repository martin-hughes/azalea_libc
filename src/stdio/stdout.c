#include <string.h>
#include <stdio.h>

#include "stdio_impl.h"

static FILE f;
FILE *const stdout = &f;
FILE *volatile __stdout_used = &f;

void __open_stdout()
{
	FILE *stdout_f = fopen("pipes\\terminal\\write", "w");
	if (stdout_f != NULL)
	{
		memcpy(stdout, stdout_f, sizeof(FILE));

		stdout->lbf = '\n';
	}
	else
	{
		exit(0);
	}
}