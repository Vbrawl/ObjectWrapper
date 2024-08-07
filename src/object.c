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
  this->reference_count = 1;
  this->destroy_callback = destroy_callback;
  this->type = type;
  return this;
}


void OWObject_Destroy(OWObject_t* this) {
  OWObject_t* const super = this->super;
  if(this->destroy_callback != NULL) this->destroy_callback(this);
  if(this->object != NULL) free(this->object);
  free(this);
  if(super != NULL) OWObject_UnRef(super);
}

OWObject_t* OWObject_FindTypeInClass(OWObject_t* this, OWID type) {
  while(this->type != type && this->super != NULL) {
    this = this->super;
  }

  if(this->type != type) return NULL;
  return this;
}

void* OWObject_FindObjectInClass(OWObject_t* this, OWID type) {
  this = OWObject_FindTypeInClass(this, type);
  if(this == NULL) return NULL;
  return this->object;
}

OWObject_t* OWObject_Ref(OWObject_t* this) {
  this->reference_count += 1;
  return this;
}

void OWObject_UnRef(OWObject_t* this) {
  this->reference_count -= 1;
  if(this->reference_count <= 0) {
    OWObject_Destroy(this);
  }
}
