#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <azalea/syscall.h>

/*void *__mmap(void *, size_t, int, int, int, off_t);*/

const char unsigned *__map_file(const char *pathname, size_t *size)
{
	struct stat st;
	unsigned char *map = MAP_FAILED;
	GEN_HANDLE map_file_handle;
	ERR_CODE ec;
	uint64_t bytes;
	uint64_t br;

	/*
	int fd = __sys_open(pathname, O_RDONLY|O_CLOEXEC|O_NONBLOCK);
	if (fd < 0) return 0;
	if (!__syscall(SYS_fstat, fd, &st)) {
		map = __mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
		*size = st.st_size;
	}
	__syscall(SYS_close, fd);*/

	ec = syscall_open_handle(pathname, strlen(pathname), &map_file_handle, 0);
	if (ec == NO_ERROR)
	{
		ec = syscall_get_handle_data_len(map_file_handle, &bytes);
		if (ec == NO_ERROR)
		{
			map = malloc(bytes);
			ec = syscall_read_handle(map_file_handle, 0, bytes, map, bytes, &br);
			if ((ec != NO_ERROR) || (br != bytes))
			{
				free(map);
				map = MAP_FAILED;
			}
		}
		syscall_close_handle(map_file_handle);
	}

	return map == MAP_FAILED ? 0 : map;
}
