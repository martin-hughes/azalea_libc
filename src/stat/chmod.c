#include <sys/stat.h>
#include <fcntl.h>

/* Known defects:
 * - This is plainly a lie.
 */

int chmod(const char *path, mode_t mode)
{
	return 0;
}
