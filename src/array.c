#include "array.h"
#include <stdlib.h>
#include <string.h>

void _OWArray_Destroy(OWO_Array_t* this);


OWO_Array_t* OWArray_Construct(size_t slot_size, size_t slots) {
  OWO_Array_t* this = _OWObject_Construct(sizeof(OWArray_t), OWID_ARRAY, NULL, _OWArray_Destroy, _OWArray_IsEqual);
  OWArray_t* const obj = this->object;

  obj->array = NULL;
  obj->slot_size = slot_size;

  obj->methods.resize = _OWArray_Resize;
  OWArray_Resize(this, slots);

  return this;
}

int _OWArray_Resize(OWO_Array_t* this, size_t slots) {
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

bool _OWArray_IsEqual(OWO_Array_t* this, OWObject_t* other) {
  OWArray_t* const obj = OWObject_FindObjectInClass(this, OWID_ARRAY);
  OWArray_t* const oobj = OWObject_FindObjectInClass(other, OWID_ARRAY);

  if(obj == oobj) return true;
  if(obj == NULL || oobj == NULL) return false;

  if(obj->array == NULL || oobj->array == NULL) return false;
  if(obj->slot_size != oobj->slot_size) return false;
  if(obj->slots != oobj->slots) return false;

  // Check the actual contents of the array
  return memcmp(obj->array, oobj->array, obj->slot_size * obj->slots) == 0;
}

void _OWArray_Destroy(OWO_Array_t* this) {
  OWArray_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
