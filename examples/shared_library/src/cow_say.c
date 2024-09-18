#include "cow_say.h"
#include <ObjectWrapper/object.h>
#include <stdio.h>

void _CowSay_Destroy(O_CowSay_t* this);


O_CowSay_t* CowSay_Construct(OWO_String_t* name) {
  O_CowSay_t* this = OWObject_Construct(CowSay_t, NULL, _CowSay_Destroy, NULL);
  if(this == NULL) return NULL;
  CowSay_t* const obj = this->object;

  obj->name = OWObject_Ref(name);
  return this;
}

void CowSay_SayHi(O_CowSay_t* this) {
  CowSay_t* const obj = OWObject_FindObjectInClass(this, OWID_CowSay_t);
  if(obj == NULL) return;

  OWO_String_t* const name = obj->name;
  printf("Cow: %s: Hello World!\n", OWString_GetBuffer(name));
}


void _CowSay_Destroy(O_CowSay_t* this) {
  CowSay_t* const obj = this->object;

  OWObject_UnRef(obj->name);
}
