#include "vector.h"



int main() {
  OWObject_t* vector = OWVector_Construct(sizeof(int), 5);
  for (int i = 0; i < 6; i++) {
    OWVector_PushBack(vector, &i);
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
  OWVector_Destroy(vector);
  return 0;
}
