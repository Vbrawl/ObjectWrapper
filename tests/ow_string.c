#include "ow_string.h"
#include <string.h>

int test_Append() {
  OWO_String_t* str = OWString_ConstructSimple("Hello");
  OWString_AppendSimple(str, "!");

  if(strcmp(OWString_GetBuffer(str), "Hello!") != 0) return -1;

  OWString_Destroy(str);
  return 0;
}

int test_Compare() {
  OWO_String_t* str1 = OWString_ConstructSimple("Hello World");
  OWO_String_t* str2 = OWString_ConstructSimple("Hello World");

  if(OWString_CompareOWString(str1, str2) != 0) return -1;

  OWString_SetSimple(str1, "Hello Worle");
  if(OWString_CompareOWString(str1, str2) <= 0) return -2;

  OWString_SetSimple(str1, "Hello World");
  OWString_SetSimple(str2, "Hello Worle");
  if(OWString_CompareOWString(str1, str2) >= 0) return -3;

  OWString_SetOWString(str1, str2);
  OWString_AppendSimple(str1, "!");
  if(OWString_CompareOWString(str1, str2) <= 0) return -4;

  OWObject_UnRef(str1);
  OWObject_UnRef(str2);
  return 0;
}


int test_Clone() {
  OWO_String_t* str1 = OWString_ConstructSimple("Hello World");
  OWO_String_t* str2 = OWString_Clone(str1);

  if(OWString_CompareOWString(str1, str2) != 0) return -1;

  OWObject_UnRef(str1);
  OWObject_UnRef(str2);
  return 0;
}



int main() {
  int error = 0;

  error = test_Append();
  if(error != 0) return error;

  error = test_Compare();
  if(error != 0) return error;

  error = test_Clone();
  if(error != 0) return error;

  return 0;
}
