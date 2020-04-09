/** @file
 *  @brief Provide thread IDs on request, since the Azalea kernel has no such concept.
 */

#include <stdint.h>
#include "atomic_arch.h"

volatile int32_t next_tid = 1;

int32_t get_new_tid()
{
  return a_fetch_add(&next_tid, 1);
}

void release_tid(int32_t _)
{
  /* Do nothing yet */
}
