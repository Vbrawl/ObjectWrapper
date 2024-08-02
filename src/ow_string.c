#include "ow_string.h"
#include <stdlib.h>
#include <string.h>


OWObject_t* OWString_Construct() {
  OWObject_t* array = OWArray_Construct(sizeof(char), 0);
  OWObject_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, NULL, array);
  OWString_t* const obj = this->object;
  obj->size = 0;

  return this;
}

int OWString_Set(OWObject_t* this, const char* content, size_t content_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  OWString_t* const obj = this->object;

  if(content_size + 1 > OWArray_GetSlots(this)) {
    OWArray_Resize(this, content_size + 1);
  }
  memcpy(OWArray_GetBuffer(this), content, sizeof(char) * content_size);
  OWArray_At(char, this, content_size) = '\0';

  return 0;
}

int OWString_Append(OWObject_t* this, const char* content, size_t content_size) {
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

  return 0;
}
