#include "vector.h"



int main() {
  DGObject_t* vector = Vector_Construct(sizeof(int), 5);
  for (int i = 0; i < 6; i++) {
    Vector_PushBack(vector, &i);
  }
  Vector_Destroy(vector);
  return 0;
}
