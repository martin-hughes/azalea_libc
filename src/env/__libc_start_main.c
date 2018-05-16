#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include "atomic.h"
#include "libc.h"

void __init_tls(size_t *);

static void dummy(void) {}
weak_alias(dummy, _init);

__attribute__((__weak__, __visibility__("hidden")))
extern void (*const __init_array_start)(void), (*const __init_array_end)(void);

static void dummy1(void *p) {}
weak_alias(dummy1, __init_ssp);

#define AUX_CNT 38

void __init_libc(char **envp, char *pn)
{
	// Set a lot of these to be invalid for the time being.
	__environ = envp;
	libc.auxv = NULL;
	__hwcap = 0;
	__sysinfo = 0;

	// Should really grab this from a system header.
	libc.page_size = 2 * 1024 * 1024;

	// I guess this should come from argv[0]
	if (!pn)
	{
		pn = "";
	}
	__progname = __progname_full = pn;
	for (int i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;

	// This appears to do nothing, but I'll forget about it if I simply delete the whole line.
	//__init_tls(aux);

	// Not ideal to initialize SSP with nullptr, but it'll do for now.
	__init_ssp(0);

	// This will do until the kernel is a bit more developed.
	struct pollfd pfd[3] = { {.fd=0}, {.fd=1}, {.fd=2} };

	libc.secure = 1;
}

static void libc_start_init(void)
{
	_init();
	uintptr_t a = (uintptr_t)&__init_array_start;
	for (; a<(uintptr_t)&__init_array_end; a+=sizeof(void(*)()))
		(*(void (**)(void))a)();
}

weak_alias(libc_start_init, __libc_start_init);

int __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv, char **envp)
{
	char *pn = NULL;
	if (argc && (argv != NULL))
	{
		pn = argv[0];
	}

	__init_libc(envp, pn);
	__libc_start_init();

	/* Pass control to the application */
	exit(main(argc, argv, envp));
	return 0;
}
