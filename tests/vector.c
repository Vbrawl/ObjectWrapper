#include "vector.h"



int main() {
  OWObject_t* vector = OWVector_Construct(sizeof(int), 5);
  for (int i = 0; i < 6; i++) {
    OWVector_PushBack(vector, &i);
  }
  OWVector_Destroy(vector);
  return 0;
}
