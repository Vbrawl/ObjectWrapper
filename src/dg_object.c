#include "dg_object.h"
#include <stdlib.h>

DGObject_t* _DGObject_Construct(size_t size, DGOI type, DGObject_t* super) {
  DGObject_t* this = malloc(sizeof(DGObject_t));
  if(this == NULL) { return NULL; }

  this->object = malloc(size);
  if(this->object == NULL) {
    free(this);
    return NULL;
  }

  this->super = super;
  this->type = type;
  return this;
}


void DGObject_Destroy(DGObject_t* this) {
  free(this->object);
  free(this);
}
