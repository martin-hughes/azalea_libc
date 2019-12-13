#include <string.h>
#include <stdio.h>

#include "stdio_impl.h"

static FILE f;
FILE *const stdout = &f;
FILE *volatile __stdout_used = &f;

void __open_stdout()
{
	FILE *stdout_f = fopen("\\proc\\0\\stdout", "w");
	if (stdout_f == NULL)
	{
		stdout_f = fopen("\\dev\\null", "w");
		if (stdout_f == NULL)
		{
			exit(-1);
		}
	}

	memcpy(stdout, stdout_f, sizeof(FILE));

	stdout->lbf = '\n';
}