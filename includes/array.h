#ifndef OW_ARRAY_H
#define OW_ARRAY_H

#include "object.h"

typedef struct OWArray_struct {
  void* array;
  size_t slots;
  size_t slot_size;
} OWArray_t;

typedef OWObject_t OWO_Array_t;

OWO_Array_t* OWArray_Construct(size_t slot_size, size_t slots);
int OWArray_Resize(OWO_Array_t* this, size_t slots);
#define OWArray_At(cast_type, this, index) ((cast_type*)((OWArray_t*)OWObject_FindTypeInClass(this, OWID_ARRAY)->object)->array)[index]
#define OWArray_GetBuffer(this) ((OWArray_t*)OWObject_FindTypeInClass(this, OWID_ARRAY)->object)->array
#define OWArray_GetSlots(this) ((OWArray_t*)OWObject_FindTypeInClass(this, OWID_ARRAY)->object)->slots
void _OWArray_Destroy(OWO_Array_t* this);
#define OWArray_Destroy OWObject_Destroy

#endif
