#include "map.h"
#include "ow_string.h"
#include <stdlib.h>
#include <string.h>
#include "ctypes.h"


int main() {
  OWO_Map_t *map;
  OWO_String_t *key1, *key2;
  OWO_Integer_t *key3;
  OWO_Integer_t *item1, *item2;
  OWO_Integer_t *temp_pointer;

  map = OWMap_Construct(5);


  key1 = OWString_ConstructSimple("key1");
  item1 = OWInteger_Construct(5);

  key2 = OWString_ConstructSimple("key2");
  item2 = OWInteger_Construct(6);

  key3 = OWInteger_Construct(5);

  OWMap_Set(map, key1, item1);
  OWMap_Set(map, key2, item2);
  OWMap_Set(map, key3, item2);


  temp_pointer = OWMap_Get(map, key1);
  if(temp_pointer == NULL) return -1;
  OWInteger_UnWrap(temp_pointer) = 1;
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWMap_Get(map, key2);
  if(temp_pointer == NULL) return -2;
  OWInteger_UnWrap(temp_pointer) = 2;
  OWObject_UnRef(temp_pointer);

  if(OWInteger_UnWrap(item1) != 1) return -3;
  if(OWInteger_UnWrap(item2) != 2) return -4;

  temp_pointer = OWMap_Get(map, key3);
  if(temp_pointer == NULL) return -5;
  OWInteger_UnWrap(temp_pointer) = 3;
  OWObject_UnRef(temp_pointer);
  if(OWInteger_UnWrap(item2) != 3) return -6;

  if(!OWMap_IsEqual(map, map)) return -7;

  OWObject_UnRef(item1);
  OWObject_UnRef(item2);

  OWObject_UnRef(key1);
  OWObject_UnRef(key2);
  OWObject_UnRef(key3);

  OWObject_UnRef(map);
  return 0;
}
