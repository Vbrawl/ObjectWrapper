#include "vector.h"
#include<stdlib.h>



int main() {
  OWObject_t* vector = OWVector_Construct(5);
  int* temp_pointer = NULL;
  int i;
  for (i = 0; i < 6; i++) {
    temp_pointer = malloc(sizeof(int));
    *temp_pointer = i;
    OWVector_PushBack(vector, temp_pointer);
  }

  if(*((int*)OWVector_Get(vector, 2)) != 2) {
    return -1;
  }

  if(OWVector_Remove(vector, 2) != 0) {
    return -2;
  }

  if(*((int*)OWVector_Get(vector, 2)) != 3) {
    return -3;
  }

  i = 100;
  OWVector_PushBack(vector, &i);
  temp_pointer = OWVector_Get(vector, OWVector_GetSize(vector) - 1);
  *temp_pointer = 101;
  if(i != 101) {
    return -4;
  }

  OWVector_Destroy(vector);
  return 0;
}
