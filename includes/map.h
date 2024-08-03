#ifndef OW_MAP_H
#define OW_MAP_H

#include "object.h"
#include "vector.h"

typedef struct OWMap_struct {
  OWObject_t* keys; // OWVector_t<OWString_t>
  OWObject_t* values; // OWVector_t<void*>
} OWMap_t;


OWObject_t* OWMap_Construct(size_t slot_steps);

// key: OWString_t
int OWMap_Set(OWObject_t* this, OWObject_t* key, void* item);
void* OWMap_Get(OWObject_t* this, OWObject_t* key);
void _OWMap_Destroy(OWObject_t* this);
#define OWMap_Destroy OWObject_Destroy

#endif
