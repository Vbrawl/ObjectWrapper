#include "ow_string.h"
#include <string.h>
#include <stdio.h>

int test_Empty() {
  OWO_String_t* str = OWString_ConstructEmpty();

  if(OWString_GetSize(str) != 0) return -1;

  OWObject_UnRef(str);
  return 0;
}

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

int test_SubString() {
  OWO_String_t* str1 = OWString_ConstructSimple("Hello World");
  OWO_String_t* str2 = OWString_SubString(str1, 6, 5);

  if(OWString_CompareSimple(str2, "World") != 0) return -1;

  OWObject_UnRef(str1);
  OWObject_UnRef(str2);
  return 0;
}

int test_FindStr() {
  OWO_String_t* str1 = OWString_ConstructSimple("Hello World");

  if(OWString_FindStrSimple(str1, "Hello") != 0) return -1;
  if(OWString_FindStrSimple(str1, "World") != 6) return -2;
  if(OWString_FindStrSimple(str1, "yolo") != -1) return -3;

  OWObject_UnRef(str1);
  return 0;
}

int test_IsEqual() {
  OWO_String_t* str1 = OWString_ConstructSimple("Hello World");
  OWO_String_t* str2 = OWString_ConstructSimple("Hello World");
  OWO_String_t* empty = OWString_ConstructEmpty();

  if(!OWString_IsEqual(str1, str2)) return -1;

  OWString_SetSimple(str2, "Hello");
  if(OWString_IsEqual(str1, str2)) return -2;

  if(OWString_IsEqual(str1, empty)) return -3;
  if(OWString_IsEqual(str2, empty)) return -4;
  if(!OWString_IsEqual(empty, empty)) return -5;

  OWObject_UnRef(empty);
  OWObject_UnRef(str2);
  OWObject_UnRef(str1);
  return 0;
}

int test_WriteIntegers() {
  int a = 'A';
  char b[sizeof(a)];
  memcpy(b, &a, sizeof(a));
  OWO_String_t* str1 = OWString_Construct(b, sizeof(b));

  if(OWString_CompareSimple(str1, "A") != 0) return -1;

  OWObject_UnRef(str1);
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

  error = test_Empty();
  if(error != 0) return error;

  error = test_SubString();
  if(error != 0) return error;

  error = test_FindStr();
  if(error != 0) return error;

  error = test_IsEqual();
  if(error != 0) return error;

  error = test_WriteIntegers();
  if(error != 0) return error;

  return 0;
}
