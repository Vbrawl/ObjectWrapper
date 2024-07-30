#ifndef DG_CLASS_H
#define DG_CLASS_H

#include <stddef.h>
#include "dg_object_identifiers.h"

#define DGOI_Register(cls, id) \
  enum { DGOI_##cls = id };

struct DGObject_struct;
typedef void(DGDestroyCallback_t)(struct DGObject_struct* this);

typedef struct DGObject_struct {
  struct DGObject_struct* super; // This is a DGObject_struct/DGObject_t pointer
  void* object;
  DGDestroyCallback_t* destroy_callback;
  DGOI type;
} DGObject_t;

#define DGObject_Construct(cls, destroy_callback, super) _DGObject_Construct(sizeof(cls), DGOI_##cls, destroy_callback, super);
#define DGObject_Super(type, cls) ((type*)cls->super->object)
DGObject_t* _DGObject_Construct(size_t size, DGOI type, DGDestroyCallback_t* destroy_callback, DGObject_t* super);
void DGObject_Destroy(DGObject_t* this);
DGObject_t* DGObject_FindTypeInClass(DGObject_t* this, DGOI type);

#endif
