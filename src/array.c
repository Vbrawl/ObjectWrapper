#include "array.h"
#include <stdlib.h>


OWO_Array_t* OWArray_Construct(size_t slot_size, size_t slots) {
  OWO_Array_t* this = _OWObject_Construct(sizeof(OWArray_t), OWID_ARRAY, _OWArray_Destroy, NULL);
  OWArray_t* const obj = this->object;

  obj->array = NULL;
  obj->slot_size = slot_size;
  OWArray_Resize(this, slots);

  return this;
}

int OWArray_Resize(OWO_Array_t* this, size_t slots) {
  OWArray_t* const obj = OWObject_FindObjectInClass(this, OWID_ARRAY);
  if(this == NULL) return -1;

  if(slots == 0) {
    if(obj->array != NULL) {
      free(obj->array);
    }
    obj->array = NULL;
    obj->slots = 0;
  }
  else {
    obj->array = realloc(obj->array, obj->slot_size * slots);
    obj->slots = slots;
    if(obj->array == NULL) return -2;
  }
  return 0;
}

void _OWArray_Destroy(OWO_Array_t* this) {
  OWArray_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
