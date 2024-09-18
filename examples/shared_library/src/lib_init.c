#include "cow_say.h"
#include "lib_init.h"

// We need to create the extern variable
OWID OWID_CowSay_t = OWID_UNDEFINED;

OWID COWSAY_LIB_init(OWID offset) {
  // We set all OWIDs while incrementing the offset
  OWID_CowSay_t = offset++;

  // Return a number AFTER the last OWID.
  return offset;
}
