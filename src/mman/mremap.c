#define _GNU_SOURCE
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include "libc.h"

#include <azalea/system_properties.h>
#include <azalea/kernel_types.h>
#include <azalea/syscall.h>

static void dummy(void) { }
weak_alias(dummy, __vm_wait);

void *__mremap(void *old_addr, size_t old_len, size_t new_len, int flags, ...)
{
	va_list ap;
	void *new_addr = 0;

	unsigned long old_start_ul = (unsigned long)old_addr;
	unsigned long old_start_page = old_start_ul - (old_start_ul % MEM_PAGE_SIZE);
	int old_extra_page = ((old_start_ul + old_len) - old_start_page) > MEM_PAGE_SIZE;
	int new_extra_page = ((old_start_ul + new_len) - old_start_page) > MEM_PAGE_SIZE;

	unsigned long old_pages = (old_len + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE;
	unsigned long new_pages = (new_len + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE;

	unsigned long cur_map_addr;

	ERR_CODE ec;

	if (old_extra_page)
	{
		old_pages++;
	}
	if (new_extra_page)
	{
		new_pages++;
	}

	if (new_len >= PTRDIFF_MAX)
	{
		errno = ENOMEM;
		return MAP_FAILED;
	}

	if (new_len == 0)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}

	if (flags & MREMAP_FIXED)
	{
		__vm_wait();
		va_start(ap, flags);
		new_addr = va_arg(ap, void *);
		va_end(ap);
	}

	/* Azalea deficiency - we don't support moves in mremap */
	if (new_addr != NULL)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}

  /* Azalea deficiency - we don't support shrinking remaps. */
	if (old_len > new_len)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}

	cur_map_addr = old_start_page + (old_pages * MEM_PAGE_SIZE);

	if (new_pages - old_pages > 0)
	{
		ec = az_allocate_backing_memory((new_pages - old_pages), (void **)&cur_map_addr);

		switch(ec)
		{
		case NO_ERROR:
			break;

		case OUT_OF_RESOURCE:
			errno = ENOMEM;
			return MAP_FAILED;
			break;

		default:
			errno = EINVAL;
			return MAP_FAILED;
			break;
		}
	}

	return (void *)old_addr;
}

weak_alias(__mremap, mremap);
