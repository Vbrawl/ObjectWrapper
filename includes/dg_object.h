#ifndef DG_CLASS_H
#define DG_CLASS_H

#include <stddef.h>
#include "dg_object_identifiers.h"

#define DGOI_Register(cls, id) \
  enum { DGOI_##cls = id };
typedef struct DGObject_struct {
  void* super; // This is a DGObject_struct/DGObject_t pointer
  void* object;
  DGOI type;
} DGObject_t;

#define DGObject_Construct(cls, super) _DGObject_Construct(sizeof(cls), DGOI_##cls, super);
DGObject_t* _DGObject_Construct(size_t size, DGOI type, DGObject_t* super);
void DGObject_Destroy(DGObject_t* this);

#endif
