#include "dg_object.h"
#include "dg_object_identifiers.h"

#include <stdio.h>


DGOI_Register(MClass_t, DGOI_USER_DEFINED + 1);
typedef struct MClass_struct {
  int hello;
} MClass_t;

DGObject_t* MClass_Construct(int hello) {
  DGObject_t* this = DGObject_Construct(MClass_t, NULL, NULL);
  if(this == NULL) return NULL;

  ((MClass_t*)this->object)->hello = hello;
  return this;
}


#define MClass_Destroy DGObject_Destroy



DGOI_Register(CMClass_t, DGOI_USER_DEFINED + 2);
typedef struct CMClass_struct {
  int* flag;
} CMClass_t;

void _CMClass_Destroy(DGObject_t* this) {
  *((CMClass_t*)this->object)->flag = 1;
};

DGObject_t* CMClass_Construct(int* flag, int hello) {
  DGObject_t* super = MClass_Construct(hello);
  DGObject_t* this = DGObject_Construct(CMClass_t, _CMClass_Destroy, super);

  ((CMClass_t*)this->object)->flag = flag;

  return this;
}

#define CMClass_hello(this) DGObject_Super(MClass_t, this)->hello
#define CMClass_Destroy DGObject_Destroy


int main() {
  DGObject_t* temp = MClass_Construct(5);
  if(temp == NULL) return -1;
  if(((MClass_t*)temp->object)->hello != 5) return -2;
  MClass_Destroy(temp);

  int flag = 0;
  DGObject_t* temp2 = CMClass_Construct(&flag, 4);
  if(CMClass_hello(temp2) != 4) return -3;
  if(CMClass_hello(temp2) != ((MClass_t*)DGObject_FindTypeInClass(temp2, DGOI_MClass_t)->object)->hello) return -4;
  CMClass_Destroy(temp2);
  if(flag != 1) return -5;
  return 0;
}
