#include "object.h"
#include "object_identifiers.h"

#include <stdio.h>


OWID_Register(MClass_t, OWID_USER_DEFINED + 1);
typedef struct MClass_struct {
  int hello;
} MClass_t;

OWObject_t* MClass_Construct(int hello) {
  OWObject_t* this = OWObject_Construct(MClass_t, NULL, NULL);
  if(this == NULL) return NULL;

  ((MClass_t*)this->object)->hello = hello;
  return this;
}


#define MClass_Destroy OWObject_Destroy



OWID_Register(CMClass_t, OWID_USER_DEFINED + 2);
typedef struct CMClass_struct {
  int* flag;
} CMClass_t;

void _CMClass_Destroy(OWObject_t* this) {
  *((CMClass_t*)this->object)->flag = 1;
};

OWObject_t* CMClass_Construct(int* flag, int hello) {
  OWObject_t* super = MClass_Construct(hello);
  OWObject_t* this = OWObject_Construct(CMClass_t, _CMClass_Destroy, super);

  ((CMClass_t*)this->object)->flag = flag;

  return this;
}

#define CMClass_hello(this) OWObject_Super(MClass_t, this)->hello
#define CMClass_Destroy OWObject_Destroy


OWObject_t* EmptyClass_Construct() {
  OWObject_t* this = _OWObject_Construct(0, OWID_UNDEFINED, NULL, NULL);

  return this;
}

int main() {
  OWObject_t* temp = MClass_Construct(5);
  if(temp == NULL) return -1;
  if(((MClass_t*)temp->object)->hello != 5) return -2;
  MClass_Destroy(temp);

  int flag = 0;
  OWObject_t* temp2 = CMClass_Construct(&flag, 4);
  if(CMClass_hello(temp2) != 4) return -3;
  if(CMClass_hello(temp2) != ((MClass_t*)OWObject_FindTypeInClass(temp2, OWID_MClass_t)->object)->hello) return -4;
  if(CMClass_hello(temp2) != (((MClass_t*)OWObject_FindObjectInClass(temp2, OWID_MClass_t))->hello)) return -5;
  CMClass_Destroy(temp2);
  if(flag != 1) return -6;


  OWObject_t* empty = EmptyClass_Construct();
  OWObject_t* empty2 = OWObject_Ref(empty);
  if(empty->object != NULL) return -7;
  OWObject_UnRef(empty);
  OWObject_UnRef(empty2);

  return 0;
}
