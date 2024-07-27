#include "dg_object.h"
#include "dg_object_identifiers.h"

#include <stdio.h>


DGOI_Register(MClass_t, DGOI_USER_DEFINED + 1);
typedef struct MClass_struct {
  int hello;
} MClass_t;

DGObject_t* MClass_Construct(int hello) {
  DGObject_t* this = DGObject_Construct(MClass_t, NULL);
  if(this == NULL) return NULL;

  ((MClass_t*)this->object)->hello = hello;
  return this;
}


#define MClass_Destroy DGObject_Destroy

int main() {
  DGObject_t* temp = MClass_Construct(5);
  if(temp == NULL) return -1;
  if(((MClass_t*)temp->object)->hello != 5) return -2;
  MClass_Destroy(temp);
  return 0;
}
