#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include "__dirent.h"
#include <string.h>

#include <azalea/azalea.h>

DIR *opendir(const char *name)
{
  GEN_HANDLE dir_h;
  DIR *dir;
  struct object_properties props;

  if (az_open_handle(name, strlen(name), &dir_h, 0) != NO_ERROR)
  {
    return 0;
  }

  if (dir_h == 0)
  {
    return 0;
  }

  if (az_get_object_properties(dir_h, NULL, 0, &props) != NO_ERROR)
  {
    az_close_handle(dir_h);
    return 0;
  }

  if (!props.exists || props.is_leaf)
  {
    az_close_handle(dir_h);
    return 0;
  }

  if (!(dir = calloc(1, sizeof *dir)))
  {
    az_close_handle(dir_h);
    return 0;
  }

  dir->dir_handle = dir_h;
  return dir;
}
