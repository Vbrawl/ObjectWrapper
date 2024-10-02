#include "ow_string.h"
#include <stdlib.h>
#include <string.h>


OWO_String_t* OWString_Construct(const char* content, size_t content_size) {
  OWO_Array_t* array = OWArray_Construct(sizeof(char), 0);
  if(array == NULL) return NULL;

  OWO_String_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, array, NULL, _OWString_IsEqual);
  if(this == NULL) {
    OWArray_Destroy(array);
    return NULL;
  }
  OWString_t* const obj = this->object;

  obj->methods.set = _OWString_Set;
  obj->methods.append = _OWString_Append;
  obj->methods.compare = _OWString_Compare;
  obj->methods.substring = _OWString_SubString;
  obj->methods.findstr = _OWString_FindStr;
  obj->methods.findstrrev = _OWString_FindStrRev;
  obj->methods.getsize = _OWString_GetSize;

  OWString_Set(this, content, content_size);
  return this;
}

int _OWString_Set(OWO_String_t* this, const char* content, size_t content_size) {
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

int _OWString_Append(OWO_String_t* this, const char* content, size_t content_size) {
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


int _OWString_Compare(OWO_String_t* this, const char* other, size_t other_size) {
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

OWO_String_t* _OWString_SubString(OWO_String_t* this, size_t start, size_t size) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
  if(obj == NULL) return NULL;

  if(size <= 0) return NULL;
  if(start < 0) return NULL;
  if(start + size > OWString_GetSize(this)) return NULL;

  OWO_String_t* sub = OWString_ConstructEmpty();
  OWString_t* const sobj = OWObject_FindObjectInClass(sub, OWID_STRING);
  OWString_Resize(sub, size + 1);

  char *buf = OWString_GetBuffer(this);
  char *sbuf = OWString_GetBuffer(sub);

  for(size_t i = 0; i < size; i++) {
    sbuf[i] = buf[i + start];
  }
  sbuf[size] = '\0';
  sobj->size = size;

  return sub;
}

size_t _OWString_FindStr(OWO_String_t* this, const char* sub, size_t sub_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  if(this == NULL) return -1;

  const char *buf = OWString_GetBuffer(this);
  const size_t bsize = OWString_GetSize(this);

  if(bsize < sub_size) return -1;

  // found:
  //    This variable signals wether a character matches
  //
  // offset:
  //    When found is false this variable is updated to `i`.
  //    When found is true this variable doesn't change but
  //    is used as an offset from the start of the word, while i
  //    continues to increment this stays the same which keeps track of
  //    the start of the word and `i` is the counter which gets the next
  //    character.

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

size_t _OWString_FindStrRev(OWO_String_t* this, const char* sub, size_t sub_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  if(this == NULL) return -1;

  const char *buf = OWString_GetBuffer(this);
  const size_t bsize = OWString_GetSize(this);

  if(bsize < sub_size) return -1;

  // found:
  //    This variable signals wether a character matches
  //
  // found_whole:
  //    This variable signals wether the whole substring was found
  //
  // offset:
  //    When found is false this variable is updated to `i`.
  //    When found is true this variable doesn't change but
  //    is used as an offset from the start of the word, while `i`
  //    continues to decrement this stays the same which keeps track of
  //    the start of the word and `i` is the counter which gets the next
  //    character.

  // end - 2 => pointer to the last character
  bool found = false;
  bool found_whole = false;
  size_t end = bsize - 1;
  size_t offset = end;
  for(size_t i = end; i != -1 && offset - i < sub_size && !found_whole; i--) {
    if(!found) offset = i;
    found = (buf[i] == sub[sub_size - (offset - i) - 1]);
    found_whole = (offset - i == sub_size - 1);
  }
  if(!found_whole) offset = -1;
  else offset = offset - sub_size + 1;

  return offset;
}

bool _OWString_IsEqual(OWO_String_t* this, OWObject_t* other) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
  OWString_t* const oobj = OWObject_FindObjectInClass(other, OWID_STRING);

  if(obj == oobj) return true;
  if(obj == NULL || oobj == NULL) return false;

  if(obj->size != oobj->size) return false;

  const char* buf = OWString_GetBuffer(this);
  const char* obuf = OWString_GetBuffer(other);

  return strncmp(buf, obuf, obj->size) == 0;
}

size_t _OWString_GetSize(OWO_String_t* this) {
  OWString_t* const obj = OWObject_FindObjectInClass(this, OWID_STRING);
  if(obj == NULL) return 0;

  size_t slots = OWArray_GetSlots(this);
  bool recalculate = false;

  if(obj->size < slots)
    recalculate = (OWArray_At(char, this, obj->size) != '\0');

  if(obj->size >= slots || recalculate)
    obj->size = strlen(OWString_GetBuffer(this));

  return obj->size;
}
