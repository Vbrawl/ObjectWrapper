#include "path.h"
#include <stdbool.h>


#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

OWO_Path_t* OWPath_ConstructWithString(OWO_String_t* string) {
  OWO_Path_t* path = _OWObject_Construct(sizeof(OWPath_t), OWID_PATH, string, NULL, NULL);
  return path;
}

OWO_Path_t* OWPath_ConstructHere() {
  OWO_String_t* str_path = OWString_ConstructEmpty();
  if(str_path == NULL) return NULL;
  OWString_Resize(str_path, PATH_MAX);

  bool error = false;
  error = (getcwd(OWString_GetBuffer(str_path), PATH_MAX) == NULL);
  if(!error) error = (OWString_Resize(str_path, OWString_GetSize(str_path)+1) != 0);

  if(error) {
    OWObject_Destroy(str_path);
    return NULL;
  }

  OWO_Path_t* path = OWPath_ConstructWithString(str_path);
  if(path == NULL) {
    OWObject_Destroy(str_path);
    return NULL;
  }

  return path;
}

OWO_Path_t* OWPath_Construct(const char* str, size_t len) {
  return OWPath_ConstructWithString(OWString_Construct(str, len));
}


bool OWPath_Exists(OWO_Path_t* this) {
  struct stat s;
  int err = stat(OWString_GetBuffer(this), &s);
  return (err == 0);
}

bool OWPath_IsDir(OWO_Path_t* this) {
  struct stat s;
  bool is_dir = false;
  int err = stat(OWString_GetBuffer(this), &s);

  if(err == 0) {
    is_dir = S_ISDIR(s.st_mode);
  }

  return is_dir;
}

bool OWPath_IsFile(OWO_Path_t* this) {
  struct stat s;
  bool is_file = false;
  int err = stat(OWString_GetBuffer(this), &s);

  if(err == 0) {
    is_file = S_ISREG(s.st_mode);
  }

  return is_file;
}
