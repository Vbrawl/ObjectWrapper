#include "dg_object.h"
#include <stdlib.h>

DGObject_t* _DGObject_Construct(size_t size, DGOI type, DGDestroyCallback_t* destroy_callback, DGObject_t* super) {
  DGObject_t* this = malloc(sizeof(DGObject_t));
  if(this == NULL) { return NULL; }

  this->object = malloc(size);
  if(this->object == NULL) {
    free(this);
    return NULL;
  }

  this->super = super;
  this->destroy_callback = destroy_callback;
  this->type = type;
  return this;
}


void DGObject_Destroy(DGObject_t* this) {
  DGObject_t* prev_this = this;
  while(this != NULL) {
    if(this->destroy_callback != NULL) {
      this->destroy_callback(this);
    }
    free(this->object);

    this = this->super;
    free(prev_this);
    prev_this = this;
  }
}

DGObject_t* DGObject_FindTypeInClass(DGObject_t* this, DGOI type) {
  while(this->type != type && this->super != NULL) {
    this = this->super;
  }

  if(this->type != type) return NULL;
  return this;
}
