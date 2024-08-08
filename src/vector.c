
#include "vector.h"
#include <stdlib.h>
#include <string.h>


OWO_Vector_t* OWVector_Construct(size_t slot_steps) {
  OWO_Array_t* array = OWArray_Construct(sizeof(OWObject_t*), slot_steps);
  OWO_Vector_t* this = _OWObject_Construct(sizeof(OWVector_t), OWID_VECTOR, _OWVector_Destroy, array);
  OWVector_t* const obj = this->object;

  obj->size = 0;
  obj->slot_steps = slot_steps;
  return this;
}

int OWVector_Insert(OWO_Vector_t* this, size_t index, OWObject_t* item) {
  int error = 0;
  OWVector_t* const obj = OWObject_FindObjectInClass(this, OWID_VECTOR);
  if(obj == NULL) return -1;
  if(index > obj->size) return -2;

  if(obj->size + 1 > OWArray_GetSlots(this)) {
    error = OWVector_Resize(this, OWArray_GetSlots(this) + obj->slot_steps);
    if(error < 0) {
      return error;
    }
  }

  if((obj->size > 0 || index > 0) && obj->size != index) {
    memmove(OWArray_GetBuffer(this) + (index + 1) * sizeof(OWObject_t*),
            OWArray_GetBuffer(this) + index * sizeof(OWObject_t*),
            (obj->size - index) * sizeof(OWObject_t*));
  }
  OWObject_Ref(item);
  OWArray_At(OWObject_t*, this, index) = item;
  obj->size += 1;

  return 0;
}

OWObject_t* OWVector_Get(OWO_Vector_t* this, size_t index) {
  OWVector_t* const obj = OWObject_FindObjectInClass(this, OWID_VECTOR);
  if(obj == NULL) return NULL;

  if(index >= obj->size) {
    return NULL;
  }

  return OWObject_Ref(OWArray_At(OWObject_t*, this, index));
}

int OWVector_Remove(OWO_Vector_t* this, size_t index) {
  OWVector_t* const obj = OWObject_FindObjectInClass(this, OWID_VECTOR);
  if(obj == NULL) return -1;

  if(index >= obj->size) {
    return -2;
  }

  OWObject_UnRef(OWArray_At(OWObject_t*, this, index));

  if(index + 1 != obj->size) {
    memmove(OWArray_GetBuffer(this) + index * sizeof(OWObject_t*),
            OWArray_GetBuffer(this) + (index + 1) * sizeof(OWObject_t*),
            (obj->size - index) * sizeof(OWObject_t*));
  }
  obj->size -= 1;

  return 0;
}

OWObject_t* OWVector_Pop(OWO_Vector_t* this, size_t index) {
  OWObject_t* item = OWVector_Get(this, index);
  OWVector_Remove(this, index);

  return item;
}

void _OWVector_Destroy(OWO_Vector_t* this) {
  OWVector_t* const obj = this->object;
  while(obj->size > 0) {
    OWVector_Remove(this, obj->size - 1);
  }
}
