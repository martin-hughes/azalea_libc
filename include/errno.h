#ifndef	_ERRNO_H
#define _ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#include <bits/errno.h>

#ifndef __AZ_KERNEL__
/* Define per-thread errno */
int *__errno_location(void);
#define errno (*__errno_location())

#else
/* Define single errno variable */
#define errno errno_one_thread
extern int errno_one_thread;
#endif

#ifdef _GNU_SOURCE
extern char *program_invocation_short_name, *program_invocation_name;
#endif

#ifdef __cplusplus
}
#endif

#endif

