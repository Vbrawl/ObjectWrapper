#include "ctypes.h"

#define CTYPE_CONSTRUCTOR(obj_name, c_type, owid) \
OWO_ ## obj_name ## _t* OW ## obj_name ## _Construct(c_type object) {\
  OWO_ ## obj_name ## _t* this = _OWObject_Construct(sizeof(c_type), owid, NULL, NULL);\
  *((c_type*)this->object) = object;\
  return this;\
}


/* Integer *
OWO_Integer_t* OWInteger_Construct(int object) {
  OWO_Integer_t* this = _OWObject_Construct(sizeof(int), OWID_INTEGER, NULL, NULL);
  *((int*)this->object) = object;
  return this;
}


/* Character *
OWO_Character_t* OWCharacter_Construct(char object) {
  OWO_Character_t* this = _OWObject_Construct(sizeof(char), OWID_CHARACTER, NULL, NULL);
  *((char*)this->object) = object;
  return this;
}


/* Boolean *
OWO_Boolean_t* OWBoolean_Construct(bool object) {
  OWO_Boolean_t* this = _OWObject_Construct(sizeof(bool), OWID_BOOLEAN, NULL, NULL);
  *((bool*)this->object) = object;
  return this;
}
*/


CTYPE_CONSTRUCTOR(Integer, int, OWID_INTEGER)

CTYPE_CONSTRUCTOR(UnsignedInteger8, uint8_t, OWID_UNSIGNED_INTEGER_8)

CTYPE_CONSTRUCTOR(Character, char, OWID_CHARACTER)

CTYPE_CONSTRUCTOR(Boolean, bool, OWID_BOOLEAN)
