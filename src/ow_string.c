#include "ow_string.h"
#include <stdlib.h>
#include <string.h>


OWObject_t* OWString_Construct() {
  OWObject_t* this = _OWObject_Construct(sizeof(OWString_t), OWID_STRING, _OWString_Destroy, NULL);
  OWString_t* const obj = this->object;
  obj->string = NULL;
  obj->length = 0;

  return this;
}

int OWString_Set(OWObject_t* this, const char* content, size_t content_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  OWString_t* const obj = this->object;

  if(content_size == 0) {
    if(obj->length > 0) {
      free(obj->string);
    }
    obj->string = NULL;
    obj->length = 0;
  }
  else {
    obj->string = realloc(obj->string, content_size + 1);
    if(obj->string == NULL) {
      return -1;
    }
    memcpy(obj->string, content, content_size);
    obj->length = content_size;
    obj->string[obj->length] = '\0';
  }
  return 0;
}

int OWString_Append(OWObject_t* this, const char* content, size_t content_size) {
  this = OWObject_FindTypeInClass(this, OWID_STRING);
  OWString_t* const obj = this->object;

  if(content_size > 0) {
    obj->string = realloc(obj->string, obj->length + content_size + 1);
    if(obj->string == NULL) {
      return -1;
    }
    memcpy(obj->string + obj->length, content, content_size);
    obj->length += content_size;
    obj->string[obj->length] = '\0';
  }

  return 0;
}

void _OWString_Destroy(OWObject_t* this) {
  OWString_t* const obj = this->object;
  if(obj->length > 0) {
    free(obj->string);
  }
}
