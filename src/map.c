#include "map.h"

void _OWMap_Destroy(OWO_Map_t* this);

OWO_Map_t* OWMap_Construct(size_t slot_steps) {
  OWO_Map_t* this = _OWObject_Construct(sizeof(OWMap_t), OWID_MAP, NULL, _OWMap_Destroy, _OWMap_IsEqual);
  if(this == NULL) {
    return NULL;
  }
  OWMap_t* const obj = this->object;

  obj->keys = OWVector_Construct(slot_steps);
  obj->values = OWVector_Construct(slot_steps);

  obj->methods.set = _OWMap_Set;
  obj->methods.unset = _OWMap_UnSet;
  obj->methods.find_entry = _OWMap_FindEntry;
  obj->methods.get = _OWMap_Get;

  return this;
}


int _OWMap_Set(OWO_Map_t* this, OWObject_t* key, OWObject_t* item) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return -1;

  size_t i = OWMap_FindEntry(this, key);
  if(i < OWMap_GetSize(this)) {
    OWVector_Remove(obj->keys, i);
    OWVector_Remove(obj->values, i);
  }
  OWVector_PushBack(obj->keys, key);
  OWVector_PushBack(obj->values, item);

  return 0;
}

int _OWMap_UnSet(OWO_Map_t* this, OWObject_t* key) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return -1;

  size_t i = OWMap_FindEntry(this, key);
  if(i > OWMap_GetSize(this)) return -2;

  OWVector_Remove(obj->keys, i);
  OWVector_Remove(obj->values, i);
  return 0;
}

size_t _OWMap_FindEntry(OWO_Map_t* this, OWObject_t* key) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return -1;

  return OWVector_FindItem(obj->keys, key);
}


OWObject_t* _OWMap_Get(OWO_Map_t* this, OWObject_t* key) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return NULL;

  size_t i = OWMap_FindEntry(this, key);
  if(i > OWMap_GetSize(this)) return NULL;

  return OWVector_Get(obj->values, i);
}

bool _OWMap_IsEqual(OWO_Map_t* this, OWObject_t* other) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  OWMap_t* const oobj = OWObject_FindObjectInClass(other, OWID_MAP);


  if(obj == oobj) return true;
  if(obj == NULL || oobj == NULL) return false;
  if(OWMap_GetSize(this) != OWMap_GetSize(other)) return false;

  OWO_Vector_t* keys = obj->keys;
  OWO_Vector_t* okeys = oobj->keys;
  for(size_t i = 0; i < OWVector_GetSize(keys); i++) {
    OWObject_t* key = OWVector_Get(keys, i);
    size_t item_index = OWVector_FindItem(okeys, key);
    OWObject_UnRef(key);

    if(item_index == -1) return false;
  }
  return true;
}


void _OWMap_Destroy(OWO_Map_t* this) {
  OWMap_t* const obj = this->object;
  OWVector_Destroy(obj->keys);
  OWVector_Destroy(obj->values);
}
