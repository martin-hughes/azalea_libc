#include <string.h>
#include <stdio.h>

#include "stdio_impl.h"

static unsigned char buf[BUFSIZ+UNGET];
static FILE f;
FILE *const stdin = &f;
FILE *volatile __stdin_used = &f;

void __open_stdin()
{
	FILE *stdin_f = fopen("proc\\0\\stdin", "r");
	if (stdin_f == NULL)
	{
		stdin_f = fopen("dev\\null", "r");
		if (stdin_f == NULL)
		{
			exit(-1);
		}
	}

	memcpy(stdin, stdin_f, sizeof(FILE));
}