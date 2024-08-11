#include <stdio.h>

#include <ObjectWrapper/object.h>
#include <ObjectWrapper/object_identifiers.h>

#include <ObjectWrapper/ow_string.h>



// Register a new OWID
// The resulting OWID is OWID_HelloClass_t
OWID_Register(HelloClass_t, OWID_USER_DEFINED + 1);

// Define the class structure
typedef struct {
  OWO_String_t* name;
} HelloClass_t;

// OPTIONAL: Create an object type for human reference
typedef OWObject_t O_HelloClass_t;



// Write destructor, constructor and a simple method
void _HelloClass_Destroy(O_HelloClass_t* this) {
  HelloClass_t* const obj = this->object;
  OWObject_UnRef(obj->name);
}

O_HelloClass_t* HelloClass_Construct(const char* name) {
  O_HelloClass_t* this = OWObject_Construct(HelloClass_t, _HelloClass_Destroy, NULL);
  if(this == NULL) return NULL;

  HelloClass_t* const obj = this->object;
  obj->name = OWString_ConstructSimple(name);
  return this;
}

int HelloClass_Greet(O_HelloClass_t* this) {
  HelloClass_t* const obj = OWObject_FindObjectInClass(this, OWID_HelloClass_t);
  if(obj == NULL) return -1;

  printf("Hello %s!\n", OWString_GetBuffer(obj->name));
  return 0;
}

// Example usage
int main() {
  O_HelloClass_t* hello = HelloClass_Construct("George");
  HelloClass_Greet(hello);
  OWObject_UnRef(hello);
}
