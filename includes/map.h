#ifndef OW_MAP_H
#define OW_MAP_H

#include "object.h"
#include "ow_string.h"
#include "vector.h"

typedef struct OWMap_struct {
  OWO_Vector_t* keys; // of OWString_t
  OWO_Vector_t* values; // of void*
} OWMap_t;

typedef OWObject_t OWO_Map_t;
#define OWO_Typed_Map_t(key_type, value_type) OWContainer_Type(OWO_Map_t, key_type, value_type)

OWO_Map_t* OWMap_Construct(size_t slot_steps);

// key: OWString_t
int OWMap_Set(OWO_Map_t* this, OWO_String_t* key, OWObject_t* item);
int OWMap_UnSet(OWO_Map_t* this, OWO_String_t* key);
OWObject_t* OWMap_Get(OWO_Map_t* this, OWO_String_t* key);
void _OWMap_Destroy(OWO_Map_t* this);
#define OWMap_GetSize(this) OWVector_GetSize(((OWMap_t*)OWObject_FindObjectInClass(this, OWID_MAP))->keys)
#define OWMap_Destroy OWObject_Destroy

#endif
