#include "map.h"
#include "ow_string.h"
#include <stdlib.h>
#include <string.h>



int main() {
  OWObject_t *map, *key1, *key2;
  const char *ckey1, *ckey2;
  int *item1, *item2;


  map = OWMap_Construct(5);

  key1 = OWString_Construct();
  ckey1 = "key1";
  OWString_Set(key1, ckey1, strlen(ckey1));

  item1 = malloc(sizeof(int));
  *item1 = 5;



  key2 = OWString_Construct();
  ckey2 = "key2";
  OWString_Set(key2, ckey2, strlen(ckey2));

  item2 = malloc(sizeof(int));
  *item2 = 4;

  OWMap_Set(map, key1, item1);
  OWMap_Set(map, key2, item2);


  *(int*)OWMap_Get(map, key1) = 1;
  *(int*)OWMap_Get(map, key2) = 2;

  if(*item1 != 1) {
    return -1;
  }

  if(*item2 != 2) {
    return -2;
  }


  OWMap_Destroy(map);
  return 0;
}
