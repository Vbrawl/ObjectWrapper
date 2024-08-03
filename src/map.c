#include "map.h"
#include "ow_string.h"



OWObject_t* OWMap_Construct(size_t slot_steps) {
  OWObject_t* this = _OWObject_Construct(sizeof(OWMap_t), OWID_MAP, _OWMap_Destroy, NULL);
  if(this == NULL) {
    return NULL;
  }
  OWMap_t* const obj = this->object;

  obj->keys = OWVector_Construct(slot_steps);
  obj->values = OWVector_Construct(slot_steps);

  return this;
}


int OWMap_Set(OWObject_t* this, OWObject_t* key, void* item) {
  this = OWObject_FindTypeInClass(this, OWID_MAP);
  OWMap_t* const obj = this->object;

  if(OWVector_GetSize(obj->keys) == 0) {
    OWVector_PushBack(obj->keys, key);
    OWVector_PushBack(obj->values, item);
  }
  else {
    OWObject_t* temp;
    int difference;
    int i = -1; // becomes 0 in the first do-while
    do {
      i += 1;
      temp = OWVector_Get(obj->keys, i);
      if(temp == NULL)
        difference = 0;
      else
        difference = OWString_Compare(key, temp);
    } while(i < OWVector_GetSize(obj->keys) && difference > 0);

    OWVector_Insert(obj->keys, i, key);
    OWVector_Insert(obj->values, i, item);
  }

  return 0;
}


void* OWMap_Get(OWObject_t* this, OWObject_t* key) {
  this = OWObject_FindTypeInClass(this, OWID_MAP);
  OWMap_t* const obj = this->object;

  OWObject_t* temp;
  int difference;
  int i = -1; // becomes 0 in the first do-while

  do {
    i += 1;
    temp = OWVector_Get(obj->keys, i);
    difference = OWString_Compare(key, temp);
  } while(i < OWVector_GetSize(obj->keys) && difference != 0);

  if(difference == 0) {
    return OWVector_Get(obj->values, i);
  }
  return NULL;
}


void _OWMap_Destroy(OWObject_t* this) {
  OWMap_t* const obj = this->object;
  OWVector_Destroy(obj->keys);
  OWVector_Destroy(obj->values);
}
