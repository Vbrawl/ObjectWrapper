#include "vector.h"
#include <stdlib.h>
#include <string.h>


OWObject_t* OWVector_Construct(size_t item_size, size_t slot_steps) {
  OWObject_t* this = _OWObject_Construct(sizeof(OWVector_t), OWID_VECTOR, _OWVector_Destroy, NULL);
  OWVector_t* const obj = this->object;

  obj->array = NULL;
  obj->size = 0;
  obj->available_slots = 0;
  obj->item_size = item_size;
  obj->slot_steps = slot_steps;
  OWVector_Resize(this, obj->slot_steps);
  return this;
}

int OWVector_Resize(OWObject_t* this, size_t slots) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  obj->array = realloc(obj->array, obj->item_size * slots);
  if(obj->array == NULL) return -2;
  obj->available_slots = slots;
  return 0;
}

int OWVector_PushBack(OWObject_t* this, void* item) {
  int error = 0;
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  if(obj->size + 1 > obj->available_slots) {
    error = OWVector_Resize(this, obj->available_slots + obj->slot_steps);
    if(error < 0) {
      return error;
    }
  }

  memcpy(obj->array + (obj->item_size * obj->size), item, obj->item_size);
  obj->size += 1;
  return error;
}

void* OWVector_Get(OWObject_t* this, size_t index) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return NULL;
  }
  OWVector_t* const obj = this->object;

  if(index >= obj->size) {
    return NULL;
  }

  return obj->array + index * obj->item_size;
}

int OWVector_Remove(OWObject_t* this, size_t index) {
  this = OWObject_FindTypeInClass(this, OWID_VECTOR);
  if(this == NULL) {
    return -1;
  }
  OWVector_t* const obj = this->object;

  if(index >= obj->size) {
    return -2;
  }

  size_t item_offset = obj->item_size * index;
  size_t next_item_offset = item_offset + obj->item_size;
  size_t size_to_move = (obj->size - index) * obj->item_size;

  memmove(
        obj->array + item_offset,
        obj->array + next_item_offset,
        size_to_move);

  return 0;
}

void _OWVector_Destroy(OWObject_t* this) {
  OWVector_t* const obj = this->object;
  if(obj->array != NULL) {
    free(obj->array);
  }
}
