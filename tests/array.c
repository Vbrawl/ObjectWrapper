#include "array.h"


int main() {
  OWObject_t* array = OWArray_Construct(sizeof(int), 5);
  OWArray_At(int, array, 0) = 51;
  if(OWArray_At(int, array, 0) != 51) return -1;

  OWArray_Destroy(array);
  return 0;
}
