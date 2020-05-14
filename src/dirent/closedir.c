#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "libc.h"

#include <azalea/azalea.h>

int closedir(DIR *dir)
{
	syscall_close_handle(dir->dir_handle);
	free(dir);
	return 0;
}
