#include "array.h"

int test_IsEqual() {
  OWO_Array_t* array = OWArray_Construct(sizeof(int), 2);
  OWArray_At(int, array, 0) = 0;
  OWArray_At(int, array, 1) = 1;

  OWO_Array_t* array2 = OWArray_Construct(sizeof(int), 2);
  OWArray_At(int, array2, 0) = 0;
  OWArray_At(int, array2, 1) = 1;

  if(!OWObject_IsEqual(array, array2)) return -1;

  OWArray_At(int, array2, 1) = 2;

  if(OWObject_IsEqual(array, array2)) return -2;

  OWObject_UnRef(array);
  OWObject_UnRef(array2);
  return 0;
}


int main() {
  OWO_Array_t* array = OWArray_Construct(sizeof(int), 5);
  OWArray_At(int, array, 0) = 51;
  if(OWArray_At(int, array, 0) != 51) return -1;

  int error = test_IsEqual();
  if(error != 0) return error;

  OWArray_Destroy(array);
  return 0;
}
