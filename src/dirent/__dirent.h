#include <azalea/kernel_types.h>

struct __dirstream
{
  GEN_HANDLE dir_handle;
  volatile int lock[1];
  uint64_t location; /* Location within directory stream */
  struct dirent last_entry; /* Entry returned by readdir() */
  char last_name[2048]; /* Last name returned by readdir() */
};
