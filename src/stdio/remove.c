#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#include <azalea/syscall.h>

int remove(const char *path)
{
	return syscall_delete_object(path);
}
