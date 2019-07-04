#include <sys/stat.h>

/* Known defects:
 * - This is plainly a lie.
 */

mode_t umask(mode_t mode)
{
	return 0777;
}
