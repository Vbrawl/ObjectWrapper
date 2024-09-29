#include "path.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define RANDOM_STRING "oaiwjdoiawjdioawjdioawjdioajwd"

int test_IsDir() {
  OWO_Path_t* path = OWPath_ConstructHere();
  if(!OWPath_IsDir(path)) return 1;
  OWString_AppendSimple(path, RANDOM_STRING);
  if(OWPath_IsDir(path)) return 2;
  OWObject_UnRef(path);
  return 0;
}

int test_Exists() {
  OWO_Path_t* path = OWPath_ConstructHere();
  if(!OWPath_Exists(path)) return 1;
  OWString_AppendSimple(path, RANDOM_STRING);
  if(OWPath_Exists(path)) return 2;
  OWObject_UnRef(path);
  return 0;
}

int test_IsFile(const char* my_name) {
  OWO_Path_t* path = OWPath_ConstructWithString(OWString_ConstructSimple(my_name));
  if(!OWPath_IsFile(path)) return 1;
  OWString_AppendSimple(path, RANDOM_STRING);
  if(OWPath_IsFile(path)) return 2;
  OWObject_UnRef(path);
  return 0;
}

int test_ConstructHere() {
  OWO_Path_t* path = OWPath_ConstructHere();
  const char* cpath = getcwd(NULL, 0);
  if(OWString_CompareSimple(path, cpath) != 0) return 1;
  free((void*)cpath);
  OWObject_UnRef(path);
  return 0;
}

int main(int argc, const char* argv[argc]) {
  int error = test_ConstructHere();
  if(error != 0) return error;

  error = test_Exists();
  if(error != 0) return error;

  error = test_IsDir();
  if(error != 0) return error;

  error = test_IsFile(argv[0]);
  if(error != 0) return error;

  return 0;
}
