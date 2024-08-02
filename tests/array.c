#include "array.h"


int main() {
  OWObject_t* array = OWArray_Construct(5);
  int i = 0;
  OWArray_At(array, 0) = &i;

  *(int*)OWArray_At(array, 0) = 1;

  if(i != 1) return -1;

  OWArray_Destroy(array);
  return 0;
}
