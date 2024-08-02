#include "array.h"
#include <stdlib.h>


OWObject_t* OWArray_Construct(size_t slots) {
  OWObject_t* this = _OWObject_Construct(sizeof(OWArray_t), OWID_ARRAY, _OWArray_Destroy, NULL);
  OWArray_t* const obj = this->object;

  OWArray_Resize(this, slots);

  return this;
}

int OWArray_Resize(OWObject_t* this, size_t slots) {
  this = OWObject_FindTypeInClass(this, OWID_ARRAY);
  if(this == NULL) {
    return -1;
  }
  OWArray_t* const obj = this->object;

  if(slots == 0) {
    if(obj->array != NULL) {
      free(obj->array);
    }
    obj->array = NULL;
    obj->slots = 0;
  }
  else {
    obj->array = realloc(obj->array, sizeof(void*) * slots);
    obj->slots = slots;
    if(obj->array == NULL) return -2;
  }
  return 0;
}

void _OWArray_Destroy(OWObject_t* this) {
  OWArray_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
