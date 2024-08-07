#include <ObjectWrapper/ctypes.h>
#include <stdio.h>


int main() {
  /*
   * We are creating an integer object (my_integer) that holds the value 5.
   *
   * In this case where we just print the value of my_integer
   * there is no reason to create a OWObject_t, but this is for
   * demonstration purposes
   */
  OWO_Integer_t* my_integer = OWInteger_Construct(5);

  printf("my_integer: %d\n", OWInteger_UnWrap(my_integer));

  /*
   * Now we want to change the value of my_integer
   * The correct way to do it is using the UnWrap function of OWInteger
   */
  OWInteger_UnWrap(my_integer) += 1;
  printf("my_integer + 1: %d\n", OWInteger_UnWrap(my_integer));


  /*
   * Now we are done with the object.
   * We need to destroy it to avoid memory leaks
   */
  OWObject_Destroy(my_integer);

  return 0;
}
