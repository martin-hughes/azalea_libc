#include <sys/mman.h>
#include <errno.h>
#include "libc.h"

#include <azalea/syscall.h>
#include <azalea/system_properties.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

int __munmap(void *start, size_t len)
{
	ERR_CODE ec;
	unsigned long start_page;
	unsigned long num_pages;
	int extra_page;
	int retval = -1;

	__vm_wait();

	start_page = ((unsigned long)start) - (start_page % MEM_PAGE_SIZE);
	extra_page = ((((unsigned long)start) + len) - start_page) > MEM_PAGE_SIZE;

	num_pages = (len + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE;
	if (extra_page)
	{
		num_pages++;
	}

	/* Azalea deficiency - this will just release the whole lot! */
	ec = az_release_backing_memory((void *)start_page);

	switch(ec)
	{
	case NO_ERROR:
		retval = 0;
		break;

	default:
		errno = EINVAL;
		break;
	}

	return retval;
}

weak_alias(__munmap, munmap);
