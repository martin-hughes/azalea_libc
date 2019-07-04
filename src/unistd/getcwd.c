#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

/* Known defects:
 * - At present, Azalea doesn't really have a concept of 'working directory' so just return the root.
 */

char *getcwd(char *buf, size_t size)
{
	char tmp[buf ? 1 : PATH_MAX];
	if (!buf) {
		buf = tmp;
		size = sizeof tmp;
	} else if (!size) {
		errno = EINVAL;
		return 0;
	}

	if (size < 2)
	{
		errno = ERANGE;
		return 0;
	}

	memcpy(buf, "\\", 2);

	return buf == tmp ? strdup(buf) : buf;
}
