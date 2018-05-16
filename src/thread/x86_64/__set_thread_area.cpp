/* Azalea-specific versino of __set_thread_area.
 *
 * Copyright Martin Hughes 2018.
 * Licenced under standard MIT licence. See COPYRIGHT for details.
 *
 * It's not ideal to have a C++ compiled file in a C library I guess, but it saves me a bit of work until I make C-
 * compatible header files.
 */

//#include "src/internal/pthread_impl.h"
#include <errno.h>
#include <azalea/syscall.h>

extern "C" int __set_thread_area(void *ptr);

int __set_thread_area(void *ptr)
{
  int ret = -1;

  ERR_CODE r = syscall_thread_set_tls_base(TLS_REGISTERS::FS, reinterpret_cast<unsigned long>(ptr));

  if (r == ERR_CODE::NO_ERROR)
  {
    ret = 0;
  }
  else
  {
    errno = EFAULT;
  }

  return ret;
}