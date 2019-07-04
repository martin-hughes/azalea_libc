#include <sys/stat.h>
#include <fcntl.h>
#include "libc.h"

/* Known defects:
 * - We don't really have symbolic links, per se...
 */

int lstat(const char *restrict path, struct stat *restrict buf)
{
	return stat(path, buf);
}

LFS64(lstat);
