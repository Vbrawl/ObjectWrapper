#ifndef OW_CLASS_H
#define OW_CLASS_H

#include <stddef.h>
#include "object_identifiers.h"

#define OWID_Register(cls, id) \
  enum { OWID_##cls = id };

struct OWObject_struct;
typedef void(OWDestroyCallback_t)(struct OWObject_struct* this);

typedef struct OWObject_struct {
  struct OWObject_struct* super; // This is a OWObject_struct/OWObject_t pointer
  void* object;
  OWDestroyCallback_t* destroy_callback;
  OWID type;
} OWObject_t;

#define OWObject_Construct(cls, destroy_callback, super) _OWObject_Construct(sizeof(cls), OWID_##cls, destroy_callback, super);
#define OWObject_Super(type, cls) ((type*)cls->super->object)
OWObject_t* _OWObject_Construct(size_t size, OWID type, OWDestroyCallback_t* destroy_callback, OWObject_t* super);
void OWObject_Destroy(OWObject_t* this);
OWObject_t* OWObject_FindTypeInClass(OWObject_t* this, OWID type);

#endif
