#include "map.h"



OWO_Map_t* OWMap_Construct(size_t slot_steps) {
  OWO_Map_t* this = _OWObject_Construct(sizeof(OWMap_t), OWID_MAP, _OWMap_Destroy, NULL);
  if(this == NULL) {
    return NULL;
  }
  OWMap_t* const obj = this->object;

  obj->keys = OWVector_Construct(slot_steps);
  obj->values = OWVector_Construct(slot_steps);

  return this;
}


int OWMap_Set(OWO_Map_t* this, OWO_String_t* key, OWObject_t* item) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return -1;

  OWObject_Ref(key);
  OWObject_Ref(item);

  if(OWVector_GetSize(obj->keys) == 0) {
    OWVector_PushBack(obj->keys, key);
    OWVector_PushBack(obj->values, item);
  }
  else {
    OWO_String_t* temp;
    int difference;
    int i = -1; // becomes 0 in the first do-while
    do {
      i += 1;
      temp = OWVector_Get(obj->keys, i);
      if(temp == NULL)
        difference = 0;
      else {
        difference = OWString_Compare(key, temp);
        OWObject_UnRef(temp);
      }
    } while(i < OWVector_GetSize(obj->keys) && difference > 0);

    if(difference == 0) {
      OWVector_Remove(obj->keys, i);
      OWVector_Remove(obj->values, i);
    }

    OWVector_Insert(obj->keys, i, key);
    OWVector_Insert(obj->values, i, item);
  }

  OWObject_UnRef(key);
  OWObject_UnRef(item);

  return 0;
}

int OWMap_UnSet(OWO_Map_t* this, OWO_Map_t* key) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return -1;

  OWObject_Ref(key);

  OWO_String_t* temp;
  int difference;
  int i = -1;

  do {
    i += 1;
    temp = OWVector_Get(obj->keys, i);
    difference = OWString_Compare(key, temp);
    OWObject_UnRef(temp);
  } while(i < OWVector_GetSize(obj->keys) && difference != 0);

  OWObject_UnRef(key);

  if(difference != 0) return -2;

  OWVector_Remove(obj->keys, i);
  OWVector_Remove(obj->values, i);
  return 0;
}


OWObject_t* OWMap_Get(OWO_Map_t* this, OWO_String_t* key) {
  OWMap_t* const obj = OWObject_FindObjectInClass(this, OWID_MAP);
  if(obj == NULL) return NULL;

  OWObject_Ref(key);

  OWO_String_t* temp;
  int difference;
  int i = -1; // becomes 0 in the first do-while

  do {
    i += 1;
    temp = OWVector_Get(obj->keys, i);
    difference = OWString_Compare(key, temp);
    OWObject_UnRef(temp);
  } while(i < OWVector_GetSize(obj->keys) && difference != 0);

  OWObject_UnRef(key);

  if(difference == 0) {
    return OWVector_Get(obj->values, i);
  }
  return NULL;
}


void _OWMap_Destroy(OWO_Map_t* this) {
  OWMap_t* const obj = this->object;
  OWVector_Destroy(obj->keys);
  OWVector_Destroy(obj->values);
}
