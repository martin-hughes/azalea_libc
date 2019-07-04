#include <unistd.h>
#include "errno.h"

/* Known defects:
 * - Plainly this ignores the fact that we might actually be connected to a terminal...
 */

int isatty(int fd)
{
	errno = ENOTTY;
	return 0;
}
