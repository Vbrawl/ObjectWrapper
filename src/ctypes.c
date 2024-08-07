#include "ctypes.h"


/* Integer */
OWO_Integer_t* OWInteger_Construct(int object) {
  OWO_Integer_t* this = _OWObject_Construct(sizeof(int), OWID_INTEGER, NULL, NULL);
  *((int*)this->object) = object;
  return this;
}


/* Character */
OWO_Character_t* OWCharacter_Construct(char object) {
  OWO_Character_t* this = _OWObject_Construct(sizeof(char), OWID_CHARACTER, NULL, NULL);
  *((char*)this->object) = object;
  return this;
}


/* Boolean */
OWO_Boolean_t* OWBoolean_Construct(bool object) {
  OWO_Boolean_t* this = _OWObject_Construct(sizeof(bool), OWID_BOOLEAN, NULL, NULL);
  *((bool*)this->object) = object;
  return this;
}
