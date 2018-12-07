#include <string.h>
#include <stdio.h>

#include "stdio_impl.h"

static FILE f;
FILE *const stderr = &f;
FILE *volatile __stderr_used = &f;

void __open_stderr()
{
	FILE *stderr_f = fopen("proc\\0\\stderr", "w");
	if (stderr_f == NULL)
	{
		stderr_f = fopen("dev\\null", "w");
		if (stderr_f == NULL)
		{
			exit(-1);
		}
	}
	memcpy(stderr, stderr_f, sizeof(FILE));
	stderr->lbf = '\n';
}