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


int test_IsEqual() {
  OWO_Vector_t* vec1 = OWVector_Construct(2);
  OWO_Vector_t* vec2 = vec1;

  OWObject_t* temp = OWInteger_Construct(5);
  OWVector_PushBack(vec1, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(4);
  OWVector_PushBack(vec1, temp);
  OWObject_UnRef(temp);

  if(!OWVector_IsEqual(vec1, vec2)) return -1;

  vec2 = OWVector_Construct(3);
  temp = OWInteger_Construct(5);
  OWVector_PushBack(vec2, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(4);
  OWVector_PushBack(vec2, temp);
  OWObject_UnRef(temp);

  if(!OWVector_IsEqual(vec1, vec2)) return -2;

  temp = OWInteger_Construct(4);
  OWVector_PushBack(vec2, temp);
  OWObject_UnRef(temp);

  if(OWVector_IsEqual(vec1, vec2)) return -3;

  OWObject_UnRef(vec1);
  OWObject_UnRef(vec2);

  return 0;
}

int test_Insert() {
  OWO_Vector_t* vector = OWVector_Construct(2);
  OWO_Integer_t* temp = OWInteger_Construct(2);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(3);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWVector_Get(vector, 0);
  if(OWInteger_UnWrap(temp) != 2) return -1;
  OWObject_UnRef(temp);

  temp = OWVector_Get(vector, 1);
  if(OWInteger_UnWrap(temp) != 3) return -2;
  OWObject_UnRef(temp);

  OWObject_UnRef(vector);
  return 0;
}

int test_Pop() {
  OWO_Vector_t* vector = OWVector_Construct(2);
  OWO_Integer_t* temp = OWInteger_Construct(2);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWVector_Pop(vector, 0);
  if(OWInteger_UnWrap(temp) != 2) return -1;
  OWObject_UnRef(temp);

  OWObject_UnRef(vector);
  return 0;
}

int test_FindIndex() {
  OWO_Vector_t* vector = OWVector_Construct(2);

  OWO_Integer_t* temp = OWInteger_Construct(1);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(2);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(3);
  OWVector_PushBack(vector, temp);
  OWObject_UnRef(temp);

  temp = OWInteger_Construct(4);
  OWVector_PushBack(vector, temp);

  if(OWVector_FindItem(vector, temp) != 3) return -1;

  OWObject_UnRef(temp);
  OWObject_UnRef(vector);
  return 0;
}


int main() {
  int error = test_Insert();
  if(error != 0) return error;

  error = test_Pop();
  if(error != 0) return error;

  error = test_IsEqual();
  if(error != 0) return error;

  error = remove_out_of_bounds();
  if(error != 0) return error;

  error = test_FindIndex();
  if(error != 0) return error;

  return 0;
}
