#include "path.h"
#include <stdbool.h>


#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

OWO_Path_t* OWPath_ConstructWithString(OWO_String_t* string) {
  OWO_Path_t* path = _OWObject_Construct(sizeof(OWPath_t), OWID_PATH, string, NULL, NULL);
  if(path == NULL) return NULL;

  OWPath_t* const obj = path->object;

  obj->methods.exists = _OWPath_Exists;
  obj->methods.isdir = _OWPath_IsDir;
  obj->methods.isfile = _OWPath_IsFile;
  obj->methods.getbasename = _OWPath_GetBaseName;
  obj->methods.getdirname = _OWPath_GetDirName;

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


bool _OWPath_Exists(OWO_Path_t* this) {
  struct stat s;
  int err = stat(OWString_GetBuffer(this), &s);
  return (err == 0);
}

bool _OWPath_IsDir(OWO_Path_t* this) {
  struct stat s;
  bool is_dir = false;
  int err = stat(OWString_GetBuffer(this), &s);

  if(err == 0) {
    is_dir = S_ISDIR(s.st_mode);
  }

  return is_dir;
}

bool _OWPath_IsFile(OWO_Path_t* this) {
  struct stat s;
  bool is_file = false;
  int err = stat(OWString_GetBuffer(this), &s);

  if(err == 0) {
    is_file = S_ISREG(s.st_mode);
  }

  return is_file;
}

OWO_Path_t* _OWPath_GetBaseName(OWO_Path_t* this) {
  size_t i = OWString_FindStrRev(this, "/", 1);
  if(i == 0 || i == -1) {
    return OWPath_Construct("/", 1);
  }

  return OWPath_ConstructWithString(OWString_SubString(this, i + 1, OWString_GetSize(this) - i - 1));
}

OWO_Path_t* _OWPath_GetDirName(OWO_Path_t* this) {
  size_t i = OWString_FindStrRev(this, "/", 1);
  if(i == 0 || i == -1) {
    return OWPath_Construct("/", 1);
  }

  return OWPath_ConstructWithString(OWString_SubString(this, 0, i));
}
