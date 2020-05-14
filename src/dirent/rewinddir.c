#include <dirent.h>
#include <unistd.h>
#include "__dirent.h"
#include "libc.h"

void rewinddir(DIR *dir)
{
  LOCK(dir->lock);
  dir->last_name[0] = 0;
  dir->location = 0;
  UNLOCK(dir->lock);
}
