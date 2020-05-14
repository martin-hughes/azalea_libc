#include <dirent.h>
#include <errno.h>
#include "__dirent.h"
#include "libc.h"
#include <string.h>

#include <azalea/azalea.h>

/* Known defects:
 * - names >= 256 bytes will cause the function to stop early. (Azalea has no defined max path size yet)
 */

struct dirent *readdir(DIR *dir)
{
  struct dirent *ret = NULL;
  uint64_t buf_size = 280;
  char buffer[280];
  char **ptr_table = (char **)(buffer);

  if (dir &&
     (syscall_enum_children(dir->dir_handle, dir->last_name, strlen(dir->last_name), 1, buffer, &buf_size) !=NO_ERROR))
  {
    if (ptr_table[0] != NULL)
    {
      strcpy(dir->last_name, ptr_table[0]);
      strcpy(dir->last_entry.d_name, ptr_table[0]);
      dir->last_entry.d_ino = 0;
      dir->location++;
      dir->last_entry.d_off = dir->location;
      dir->last_entry.d_reclen = sizeof(struct dirent);
      dir->last_entry.d_type = DT_UNKNOWN;

      ret = &dir->last_entry;
    }
  }

  return ret;
}

LFS64(readdir);
