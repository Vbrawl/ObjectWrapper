#include "map.h"
#include "ow_string.h"
#include <stdlib.h>
#include <string.h>
#include "ctypes.h"


int main() {
  OWO_Map_t *map;
  OWO_String_t *key1, *key2;
  const char *ckey1, *ckey2;
  OWO_Integer_t *item1, *item2;
  OWO_Integer_t *temp_pointer;


  map = OWMap_Construct(5);

  key1 = OWString_Construct();
  ckey1 = "key1";
  OWString_Set(key1, ckey1, strlen(ckey1));

  item1 = OWInteger_Construct(5);



  key2 = OWString_Construct();
  ckey2 = "key2";
  OWString_Set(key2, ckey2, strlen(ckey2));

  item2 = OWInteger_Construct(6);

  OWMap_Set(map, key1, item1);
  OWMap_Set(map, key2, item2);


  temp_pointer = OWMap_Get(map, key1);
  *((int*)temp_pointer->object) = 1;
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWMap_Get(map, key2);
  *((int*)temp_pointer->object) = 2;
  OWObject_UnRef(temp_pointer);

  if(*((int*)item1->object) != 1) {
    return -1;
  }

  if(*((int*)item2->object) != 2) {
    return -2;
  }
  OWObject_UnRef(item1);
  OWObject_UnRef(item2);


  OWO_String_t* temp;
  OWMap_t* map_obj = OWObject_FindObjectInClass(map, OWID_MAP);
  while(OWMap_GetSize(map) > 0) {
    temp = OWVector_Get(map_obj->keys, 0);

    if(OWMap_UnSet(map, temp) != 0) return -3;
    OWObject_UnRef(temp);
  }

  OWObject_UnRef(key1);
  OWObject_UnRef(key2);
  OWObject_UnRef(map);
  return 0;
}
