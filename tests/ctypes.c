#include "ctypes.h"
#include "object.h"


int main() {

  OWO_Integer_t* number = OWInteger_Construct(5);
  if(OWInteger_UnWrap(number) != 5) return -1;
  OWObject_UnRef(number);

  OWO_Character_t* character = OWCharacter_Construct('a');
  if(OWCharacter_UnWrap(character) != 'a') return -2;
  OWObject_UnRef(character);

  OWO_Boolean_t* boolean = OWCharacter_Construct(true);
  if(OWBoolean_UnWrap(boolean) != true) return -3;
  OWObject_UnRef(boolean);

  return 0;
}
