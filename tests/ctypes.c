#include "ctypes.h"
#include "object.h"


int test_IsEqual() {
  OWO_Integer_t* number = OWInteger_Construct(5);
  OWO_Integer_t* number2 = OWInteger_Construct(5);

  if(!OWObject_IsEqual(number, number2)) return -1;
  OWInteger_UnWrap(number2) = 4;
  if(OWObject_IsEqual(number, number2)) return -2;

  OWObject_UnRef(number);
  OWObject_UnRef(number2);
  return 0;
}


int main() {

  OWO_Integer_t* number = OWInteger_Construct(5);
  if(OWInteger_UnWrap(number) != 5) return -1;
  OWObject_UnRef(number);

  OWO_UnsignedInteger8_t* number8 = OWUnsignedInteger8_Construct(5);
  if(OWUnsignedInteger8_UnWrap(number8) != 5) return -1;
  OWObject_UnRef(number8);

  OWO_Character_t* character = OWCharacter_Construct('a');
  if(OWCharacter_UnWrap(character) != 'a') return -2;
  OWObject_UnRef(character);

  OWO_Boolean_t* boolean = OWCharacter_Construct(true);
  if(OWBoolean_UnWrap(boolean) != true) return -3;
  OWObject_UnRef(boolean);

  return test_IsEqual();
}
