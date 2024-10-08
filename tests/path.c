#include "path.h"

#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
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

int test_GetBaseName() {
  OWO_Path_t* path = OWPath_ConstructHere();
  OWO_Path_t* basen = OWPath_GetBaseName(path);

  const char* bn = basename(OWString_GetBuffer(path));

  if(OWString_CompareSimple(basen, bn) != 0) return 1;

  OWObject_UnRef(basen);
  OWObject_UnRef(path);
  return 0;
}

int test_GetDirName() {
  OWO_Path_t* path = OWPath_ConstructHere();
  OWO_Path_t* dirn = OWPath_GetDirName(path);

  const char* dn = dirname(OWString_GetBuffer(path));

  if(OWString_CompareSimple(dirn, dn) != 0) return 1;

  OWObject_UnRef(dirn);
  OWObject_UnRef(path);
  return 0;
}

int test_Join() {
  OWO_Path_t* dir1 = OWPath_ConstructWithString(OWString_ConstructSimple("Dir1"));
  OWO_Path_t* dir2 = OWPath_ConstructWithString(OWString_ConstructSimple("Dir2"));
  OWO_Path_t* expected_result = OWPath_ConstructWithString(OWString_ConstructSimple("Dir1/Dir2"));

  OWO_Path_t* result = OWPath_Join(dir1, dir2);
  if(OWString_CompareOWString(expected_result, result) != 0) return 1;

  OWObject_UnRef(result);
  OWObject_UnRef(expected_result);
  OWObject_UnRef(dir2);
  OWObject_UnRef(dir1);
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

  error = test_GetBaseName();
  if(error != 0) return error;

  error = test_GetDirName();
  if(error != 0) return error;

  error = test_Join();
  if(error != 0) return error;

  return 0;
}
