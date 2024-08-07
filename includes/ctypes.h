#ifndef OW_CTYPES_H
#define OW_CTYPES_H

#include "object.h"
#include <stdbool.h>

/* Integer */
typedef OWObject_t OWO_Integer_t;
OWO_Integer_t* OWInteger_Construct(int object);


/* Character */
typedef OWObject_t OWO_Character_t;
OWO_Character_t* OWCharacter_Construct(char object);


/* Boolean */
typedef OWObject_t OWO_Boolean_t;
OWO_Boolean_t* OWBoolean_Construct(bool object);



#endif
