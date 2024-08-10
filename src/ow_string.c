#include "ow_string.h"
#include <stdlib.h>


OWO_String_t* OWString_Construct(const char* content, size_t content_size) {
  OWO_Array_t* array = OWArray_Construct(sizeof(char), 0);
  if(array == NULL) return NULL;

  OWO_String_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, NULL, array);
  if(this == NULL) {
    OWArray_Destroy(array);
    return NULL;
  }

  OWString_Set(this, content, content_size);
  return this;
}

int OWString_Set(OWO_String_t* this, const char* content, size_t content_size) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);

  if(content_size + 1 > OWArray_GetSlots(this)) {
    OWArray_Resize(this, content_size + 1);
  }
  memcpy(OWArray_GetBuffer(this), content, sizeof(char) * content_size);
  OWArray_At(char, this, content_size) = '\0';
  obj->size = content_size;

  return 0;
}

int OWString_Append(OWO_String_t* this, const char* content, size_t content_size) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
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


int OWString_Compare(OWO_String_t* this, const char* other, size_t other_size) {
  int i, difference;
  size_t size = OWString_GetSize(this);
  const char *str = OWString_GetBuffer(this);

  // Perform size checks
  if(size > other_size) {
    return str[other_size];
  }
  else if(size < other_size) {
    return other[size];
  }

  // Perform value checks
  for (i = 0; i < size; i++) {
    difference = str[i] - other[i];
    if(difference != 0) return difference;
  }

  return 0;
}
