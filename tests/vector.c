#include "vector.h"
#include "ctypes.h"
#include<stdlib.h>


int remove_out_of_bounds() {

  /*
   * This tests whether the vector can remove items that are out of bounds.
   */

  OWO_Vector_t* vector = OWVector_Construct(2);
  OWO_Integer_t* temp;


  temp = OWInteger_Construct(2);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(2);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  OWObject_UnRef(vector);
  return 0;
}


int main() {
  OWO_Vector_t* vector = OWVector_Construct(5);
  OWO_Integer_t* temp_pointer = NULL;
  int i;
  for (i = 0; i < 6; i++) {
    temp_pointer = OWInteger_Construct(i);
    if(OWVector_PushBack(vector, temp_pointer) != 0) {
      return 1;
    }
    OWObject_UnRef(temp_pointer);
  }

  temp_pointer = (OWO_Integer_t*)OWVector_Get(vector, 2);
  if(*((int*)temp_pointer->object) != 2) {
    return -1;
  }
  OWObject_UnRef(temp_pointer);

  if(OWVector_Remove(vector, 2) != 0) {
    return -2;
  }

  temp_pointer = (OWO_Integer_t*)OWVector_Get(vector, 2);
  if(*((int*)temp_pointer->object) != 3) {
    return -3;
  }
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWInteger_Construct(101);
  OWVector_PushFront(vector, temp_pointer);
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWVector_Get(vector, 0);
  *(int*)temp_pointer->object = 101;
  OWObject_UnRef(temp_pointer);

  int size = OWVector_GetSize(vector);
  temp_pointer = OWVector_PopFront(vector);
  if(temp_pointer == NULL) {
    return -5;
  }
  if(OWVector_GetSize(vector) == size) {
    return -6;
  }
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWInteger_Construct(2);
  OWVector_Insert(vector, 1, temp_pointer);
  OWObject_UnRef(temp_pointer);

  temp_pointer = OWVector_Pop(vector, 1);
  if(temp_pointer == NULL) {
    return -7;
  }
  if(OWVector_GetSize(vector) == size) {
    return -8;
  }

  OWObject_UnRef(temp_pointer);

  OWVector_Destroy(vector);

  return remove_out_of_bounds();
}
