#include "vector.h"
#include <stdlib.h>
#include <string.h>


DGObject_t* Vector_Construct(size_t item_size, size_t slot_steps) {
  DGObject_t* this = _DGObject_Construct(sizeof(Vector_t), DGOI_VECTOR, _Vector_Destroy, NULL);
  Vector_t* const obj = this->object;

  obj->array = NULL;
  obj->size = 0;
  obj->available_slots = 0;
  obj->item_size = item_size;
  obj->slot_steps = slot_steps;
  Vector_Resize(this, obj->slot_steps);
  return this;
}

int Vector_Resize(DGObject_t* this, size_t slots) {
  this = DGObject_FindTypeInClass(this, DGOI_VECTOR);
  if(this == NULL) {
    return -1;
  }
  Vector_t* const obj = this->object;

  obj->array = realloc(obj->array, obj->item_size * slots);
  if(obj->array == NULL) return -2;
  obj->available_slots = slots;
  return 0;
}

int Vector_PushBack(DGObject_t* this, void* item) {
  int error = 0;
  this = DGObject_FindTypeInClass(this, DGOI_VECTOR);
  if(this == NULL) {
    return -1;
  }
  Vector_t* const obj = this->object;

  if(obj->size + 1 > obj->available_slots) {
    error = Vector_Resize(this, obj->available_slots + obj->slot_steps);
    if(error < 0) {
      return error;
    }
  }

  memcpy(obj->array + (obj->item_size * obj->size), item, obj->item_size);
  obj->size += 1;
  return error;
}

void* Vector_Get(DGObject_t* this, size_t index) {
  this = DGObject_FindTypeInClass(this, DGOI_VECTOR);
  if(this == NULL) {
    return NULL;
  }
  Vector_t* const obj = this->object;

  if(index >= obj->size) {
    return NULL;
  }

  return obj->array + index * obj->item_size;
}

void _Vector_Destroy(DGObject_t* this) {
  Vector_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
