#ifndef OW_STRING_H
#define OW_STRING_H

#include "object.h"
#include "array.h"
#include <string.h>

typedef struct OWString_struct {
  size_t size; // This does NOT count the NULL-byte
} OWString_t;

typedef OWObject_t OWO_String_t;

OWO_String_t* OWString_Construct(const char* content, size_t content_size);
#define OWString_ConstructSimple(content) OWString_Construct(content, strlen(content))
#define OWString_Clone(this) OWString_Construct(OWString_GetBuffer(this), OWString_GetSize(this))

int OWString_Set(OWO_String_t* this, const char* content, size_t content_size);
#define OWString_SetSimple(this, content) OWString_Set(this, content, strlen(content))
#define OWString_SetOWString(this, other) OWString_Set(this, OWString_GetBuffer(other), OWString_GetSize(other))

int OWString_Append(OWO_String_t* this, const char* content, size_t content_size);
#define OWString_AppendSimple(this, content) OWString_Append(this, content, strlen(content))
#define OWString_AppendOWString(this, other) OWString_Append(this, OWString_GetBuffer(other), OWString_GetSize(other))

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
int OWString_Compare(OWO_String_t* this, const char* other, size_t other_size);
#define OWString_CompareSimple(this, other) OWString_Compare(this, other, strlen(other))
#define OWString_CompareOWString(this, other) OWString_Compare(this, OWString_GetBuffer(other), OWString_GetSize(other))

#define OWString_GetBuffer(this) ((char*)OWArray_GetBuffer(this))
#define OWString_GetSize(this) ((OWString_t*)OWObject_FindObjectInClass(this, OWID_STRING))->size
#define OWString_GetLength OWString_GetSize
#define OWString_Resize OWArray_Resize
#define OWString_Destroy OWObject_Destroy

#endif
