#ifndef OW_ARRAY_H
#define OW_ARRAY_H

#include "object.h"

typedef struct OWArray_struct {
  void** array;
  size_t slots;
} OWArray_t;

OWObject_t* OWArray_Construct(size_t slots);
int OWArray_Resize(OWObject_t* this, size_t slots);
#define OWArray_At(this, index) ((OWArray_t*)OWObject_FindTypeInClass(this, OWID_ARRAY)->object)->array[index]
void _OWArray_Destroy(OWObject_t* this);
#define OWArray_Destroy OWObject_Destroy

#endif
