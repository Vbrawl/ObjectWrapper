#include "ow_string.h"
#include <string.h>


int main() {
  OWObject_t* str = OWString_Construct();
  if(OWString_Set(str, "Hello", 5) < 0) {
    return -1;
  }

  if(strncmp(OWString_GetBuffer(str), "Hello", OWString_GetLength(str) != 0)) {
    return -2;
  }

  if(OWString_Append(str, " World", 6) < 0) {
    return -3;
  }

  if(strncmp(OWString_GetBuffer(str), "Hello World", OWString_GetLength(str) != 0)) {
    return -4;
  }

  OWString_Destroy(str);
  return 0;
}
