#include "lib_init.h"
#include "cow_say.h"
#include <ObjectWrapper/ow_string.h>
#include <stdio.h>


int main() {
  OWID offset = OWID_USER_DEFINED;
  offset = COWSAY_LIB_init(offset);
  // If we had another lib we would do:
  // offset = OTHER_LIB_init(offset);

  OWO_String_t* name = OWString_ConstructSimple("George");
  O_CowSay_t* cow = CowSay_Construct(name);
  OWObject_UnRef(name);

  CowSay_SayHi(cow);
  OWObject_UnRef(cow);

  printf("OWID_CowSay_t: %d\n", OWID_CowSay_t);
  return 0;
}
