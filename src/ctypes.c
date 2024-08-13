#include "ctypes.h"
#include <string.h>
#include <stdlib.h>

void _OWCType_Destroy(OWO_CType_t* this);

#define CTYPE_CONSTRUCTOR(obj_name, c_type) \
OWO_ ## obj_name ## _t* OW ## obj_name ## _Construct(c_type object) {\
  OWO_CType_t* this = _OWObject_Construct(sizeof(OWCType_t), OWID_CTYPE, NULL, _OWCType_Destroy, OWCType_IsEqual);\
  if(this == NULL) return NULL;\
  OWCType_t* obj = this->object;\
  obj->size = sizeof(c_type);\
  obj->value = malloc(obj->size);\
  if(obj->value == NULL) {\
    OWObject_Destroy(this);\
    return NULL;\
  }\
  *((c_type*)obj->value) = object;\
  return this;\
}

bool OWCType_IsEqual(OWO_CType_t* this, OWObject_t* other) {
  OWCType_t* obj = OWObject_FindObjectInClass(this, OWID_CTYPE);
  OWCType_t* oobj = OWObject_FindObjectInClass(other, OWID_CTYPE);

  if(obj == oobj) return true;
  if(obj == NULL || oobj == NULL) return false;

  if(obj->size != oobj->size) return false;
  return memcmp(obj->value, oobj->value, obj->size) == 0;
}

void _OWCType_Destroy(OWO_CType_t* this) {
  OWCType_t* const obj = this->object;
  if(obj->value != NULL) free(obj->value);
}


CTYPE_CONSTRUCTOR(Integer, int)
CTYPE_CONSTRUCTOR(UnsignedInteger8, uint8_t)
CTYPE_CONSTRUCTOR(Character, char)
CTYPE_CONSTRUCTOR(Boolean, bool)
