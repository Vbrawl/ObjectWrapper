#include "ow_string.h"
#include <string.h>

int test_OWString_Compare() {
  OWO_String_t* str1 = OWString_Construct();
  OWO_String_t* str2 = OWString_Construct();

  const char* cstr = "Hello World";
  OWString_Set(str1, cstr, strlen(cstr));
  OWString_Set(str2, cstr, strlen(cstr));

  if(OWString_Compare(str1, str2) != 0) {
    return -1;
  }

  cstr = "Hello Worle";
  OWString_Set(str1, cstr, strlen(cstr));
  if(OWString_Compare(str1, str2) <= 0) {
    return -2;
  }

  OWString_Set(str1, OWString_GetBuffer(str2), OWString_GetSize(str2));
  OWString_Set(str2, cstr, strlen(cstr));
  if(OWString_Compare(str1, str2) >= 0) {
    return -3;
  }

  OWString_Set(str1, OWString_GetBuffer(str2), OWString_GetSize(str2));
  OWString_Append(str1, "!", 1);
  if(OWString_Compare(str1, str2) <= 0) {
    return -4;
  }

  OWObject_UnRef(str1);
  OWObject_UnRef(str2);

  return 0;
}

int main() {
  int error = 0;
  OWO_String_t* str = OWString_Construct();
  if(OWString_Set(str, "Hello", 5) < 0) {
    return -1;
  }

  if(strncmp(OWString_GetBuffer(str), "Hello", OWString_GetLength(str)) != 0) {
    return -2;
  }

  if(OWString_Append(str, " World", 6) < 0) {
    return -3;
  }

  if(strncmp(OWString_GetBuffer(str), "Hello World", OWString_GetLength(str)) != 0) {
    return -4;
  }

  error = test_OWString_Compare();
  if(error != 0) {
    return -5;
  }

  OWObject_UnRef(str);
  return 0;
}
