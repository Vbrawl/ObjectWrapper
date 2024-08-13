#include "ow_string.h"
#include <stdlib.h>
#include <string.h>


OWO_String_t* OWString_Construct(const char* content, size_t content_size) {
  OWO_Array_t* array = OWArray_Construct(sizeof(char), 0);
  if(array == NULL) return NULL;

  OWO_String_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, array, NULL, NULL);
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

  if(content == NULL) {
    memset(OWArray_GetBuffer(this), 0, sizeof(char) * content_size + 1);
  }
  else {
    memcpy(OWArray_GetBuffer(this), content, sizeof(char) * content_size);
    OWArray_At(char, this, content_size) = '\0';
  }
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

OWO_String_t* OWString_SubString(OWO_String_t* this, size_t start, size_t size) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
  if(obj == NULL) return NULL;

  if(size <= 0) return NULL;
  if(start < 0) return NULL;
  if(start + size > OWString_GetSize(this)) return NULL;

  OWO_String_t* sub = OWString_ConstructEmpty();
  OWString_Resize(sub, size + 1);

  char *buf = OWString_GetBuffer(this);
  char *sbuf = OWString_GetBuffer(sub);

  for(size_t i = 0; i < size; i++) {
    sbuf[i] = buf[i + start];
  }
  sbuf[size] = '\0';
  OWString_GetSize(sub) = size;

  return sub;
}

size_t OWString_FindStr(OWO_String_t* this, const char* sub, size_t sub_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  if(this == NULL) return -1;

  const char *buf = OWString_GetBuffer(this);
  const size_t bsize = OWString_GetSize(this);

  if(bsize < sub_size) return -1;

  bool found = false;
  size_t offset = 0;
  size_t end = bsize - sub_size;
  for(size_t i = 0; i < bsize && i - offset < sub_size && offset < end; i++) {
    if(!found) offset = i;
    found = (buf[i] == sub[i - offset]);
  }
  if(!found) offset = -1;

  return offset;
}

bool OWString_IsEqual(OWO_String_t* this, OWObject_t* other) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
  OWString_t* const oobj = OWObject_FindObjectInClass(other, OWID_STRING);

  if(obj == oobj) return true;
  if(obj == NULL || oobj == NULL) return false;

  if(obj->size != oobj->size) return false;

  const char* buf = OWString_GetBuffer(this);
  const char* obuf = OWString_GetBuffer(other);

  return strncmp(buf, obuf, obj->size) == 0;
}
