#ifndef OW_CTYPES_H
#define OW_CTYPES_H

#include "object.h"
#include <stdbool.h>

/* Integer */
typedef OWObject_t OWO_Integer_t;
OWO_Integer_t* OWInteger_Construct(int object);
#define OWInteger_UnWrap(this) (*(int*)this->object)


/* Character */
typedef OWObject_t OWO_Character_t;
OWO_Character_t* OWCharacter_Construct(char object);
#define OWCharacter_UnWrap(this) (*(char*)this->object)


/* Boolean */
typedef OWObject_t OWO_Boolean_t;
OWO_Boolean_t* OWBoolean_Construct(bool object);
#define OWBoolean_UnWrap(this) (*(bool*)this->object)



#endif
