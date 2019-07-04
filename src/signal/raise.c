#include <signal.h>
#include <stdint.h>
#include <assert.h>
#include "pthread_impl.h"

/* Known defects:
 * - Azalea doesn't support signals at all! So, if this function is called, we can only really abort.
 */

int raise(int sig)
{
	assert(0);
}
