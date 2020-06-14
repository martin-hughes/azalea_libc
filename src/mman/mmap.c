#include <azalea/syscall.h>
#include <azalea/system_properties.h>

#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>
#include "libc.h"

#define UNIT SYSCALL_MMAP2_UNIT
#define OFF_MASK ((-0x2000ULL << (8*sizeof(syscall_arg_t)-1)) | (UNIT-1))

void *__mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
	ERR_CODE ec;
	unsigned long start_ul = (unsigned long)start;
	unsigned long start_page = start_ul - (start_ul % MEM_PAGE_SIZE);
	int extra_page = ((start_ul + len) - start_page) > MEM_PAGE_SIZE;

	unsigned long pages = (len + MEM_PAGE_SIZE - 1) / MEM_PAGE_SIZE;
	if (extra_page)
	{
		pages++;
	}

	/* Azalea defect: I feel like this is important, but I don't know what it's for.
	if (off & OFF_MASK)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}
	if (len >= PTRDIFF_MAX)
	{
		errno = ENOMEM;
		return MAP_FAILED;
	}*/

	if (flags & MAP_FIXED)
	{
		errno = EINVAL;
		return MAP_FAILED;
	}

	ec = az_allocate_backing_memory(pages, (void **)&start_page);
	if (ec != NO_ERROR)
	{
		switch(ec)
		{
		OUT_OF_RESOURCE:
			errno = ENOMEM;
			break;

		default:
			errno = EINVAL;
			break;
		}

		start_page = (unsigned long)NULL;
	}

	return (void *)start_page;
}

weak_alias(__mmap, mmap);

LFS64(mmap);
