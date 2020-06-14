#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#include <azalea/syscall.h>

int remove(const char *path)
{
	return az_delete_object(path, strlen(path));
}
