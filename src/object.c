#include "object.h"
#include <stdlib.h>

OWObject_t* _OWObject_Construct(size_t size, OWID type, OWDestroyCallback_t* destroy_callback, OWObject_t* super) {
  OWObject_t* this = malloc(sizeof(OWObject_t));
  if(this == NULL) { return NULL; }

  this->object = NULL;
  if(size > 0) {
    this->object = malloc(size);
    if(this->object == NULL) {
      free(this);
      return NULL;
    }
  }

  this->super = super;
  this->destroy_callback = destroy_callback;
  this->type = type;
  return this;
}


void OWObject_Destroy(OWObject_t* this) {
  OWObject_t* prev_this = this;
  while(this != NULL) {
    if(this->destroy_callback != NULL) {
      this->destroy_callback(this);
    }
    if(this->object != NULL) {
      free(this->object);
    }

    this = this->super;
    free(prev_this);
    prev_this = this;
  }
}

OWObject_t* OWObject_FindTypeInClass(OWObject_t* this, OWID type) {
  while(this->type != type && this->super != NULL) {
    this = this->super;
  }

  if(this->type != type) return NULL;
  return this;
}
