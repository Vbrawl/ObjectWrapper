#include "ow_string.h"
#include <stdlib.h>
#include <string.h>


OWO_String_t* OWString_Construct() {
  OWO_Array_t* array = OWArray_Construct(sizeof(char), 0);
  OWO_String_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, NULL, array);
  OWString_t* const obj = this->object;
  obj->size = 0;

  return this;
}

int OWString_Set(OWO_String_t* this, const char* content, size_t content_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  OWString_t* const obj = this->object;

  if(content_size + 1 > OWArray_GetSlots(this)) {
    OWArray_Resize(this, content_size + 1);
  }
  memcpy(OWArray_GetBuffer(this), content, sizeof(char) * content_size);
  OWArray_At(char, this, content_size) = '\0';
  obj->size = content_size;

  return 0;
}

int OWString_Append(OWO_String_t* this, const char* content, size_t content_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  OWString_t* const obj = this->object;
  size_t final_size = obj->size + content_size;

  if(final_size + 1 > OWArray_GetSlots(this)) {
    OWArray_Resize(this, final_size + 1);
  }

  if(content_size > 0) {
    memcpy(OWArray_GetBuffer(this) + obj->size * sizeof(char), content, sizeof(char) * content_size);
    OWArray_At(char, this, final_size) = '\0';
  }
  obj->size = final_size;

  return 0;
}


int OWString_Compare(OWO_String_t* this, OWO_String_t* other) {
  int i, difference;
  size_t size1, size2;
  const char *str1, *str2;

  // Initialize variables
  size1 = OWString_GetSize(this);
  size2 = OWString_GetSize(other);

  str1 = OWString_GetBuffer(this);
  str2 = OWString_GetBuffer(other);

  // Perform size checks
  if(size1 > size2) {
    return str1[size2];
  }
  else if(size1 < size2) {
    return str2[size1];
  }

  // Perform value checks
  for (int i = 0; i < size1; i++) {
    difference = str1[i] - str2[i];
    if(difference != 0) return difference;
  }

  return 0;
}
