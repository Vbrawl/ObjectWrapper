#ifndef OW_STRING_H
#define OW_STRING_H

#include "object.h"
#include "array.h"

typedef struct OWString_struct {
  size_t size; // This does NOT count the NULL-byte
} OWString_t;

typedef OWObject_t OWO_String_t;

OWO_String_t* OWString_Construct();
#define OWString_Resize OWArray_Resize
int OWString_Set(OWO_String_t* this, const char* content, size_t content_size);
int OWString_Append(OWO_String_t* this, const char* content, size_t content_size);

/*
 * return code:
 *    == 0: Both strings are equal
 *    > 0: The first string is greater than the second
 *    < 0: The second string is greater than the first
 *
 * example:
 *    OWString_Compare("Hello World", "Hello World") => 0
 *    OWString_Compare("Hello Worle", "Hello World") => 1
 *    OWString_Compare("Hello World", "Hello Worle") => -1
 *    OWString_Compare("Hello World!", "Hello World") => 33
 *    OWString_Compare("Hello World", "Hello World!") => -33
 */
int OWString_Compare(OWO_String_t* this, OWO_String_t* other);
#define OWString_GetBuffer(this) OWArray_GetBuffer(this)
#define OWString_GetSize(this) ((OWString_t*)OWObject_FindObjectInClass(this, OWID_STRING))->size
#define OWString_GetLength OWString_GetSize
#define OWString_Destroy OWObject_Destroy

#endif
