#include "vector.h"
#include<stdlib.h>



int main() {
  OWO_Vector_t* vector = OWVector_Construct(5);
  int* temp_pointer = NULL;
  int i;
  for (i = 0; i < 6; i++) {
    temp_pointer = malloc(sizeof(int));
    *temp_pointer = i;
    if(OWVector_PushBack(vector, temp_pointer) != 0) {
      return 1;
    }
  }

  temp_pointer = (int*)OWVector_Get(vector, 2);
  if(*temp_pointer != 2) {
    return -1;
  }

  if(OWVector_Remove(vector, 2) != 0) {
    return -2;
  }

  if(*((int*)OWVector_Get(vector, 2)) != 3) {
    return -3;
  }

  free(temp_pointer);

  i = 100;
  OWVector_PushFront(vector, &i);
  temp_pointer = OWVector_Get(vector, 0);
  *temp_pointer = 101;
  if(i != 101) {
    return -4;
  }

  int size = OWVector_GetSize(vector);
  temp_pointer = OWVector_PopFront(vector);
  if(temp_pointer == NULL) {
    return -5;
  }
  if(OWVector_GetSize(vector) == size) {
    return -6;
  }

  OWVector_Insert(vector, 1, &i);
  temp_pointer = OWVector_Pop(vector, 1);
  if(temp_pointer == NULL) {
    return -7;
  }
  if(OWVector_GetSize(vector) == size) {

  }
  *temp_pointer = 102;
  if(i != 102) {
    return -8;
  }

  while(OWVector_GetSize(vector) != 0) {
    size = OWVector_GetSize(vector);
    temp_pointer = OWVector_PopBack(vector);

    if(temp_pointer == NULL) {
      return -9;
    }
    free(temp_pointer);

    if(OWVector_GetSize(vector) == size) {
      return -10;
    }
  }

  OWVector_Destroy(vector);
  return 0;
}
