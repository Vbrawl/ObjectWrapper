#ifndef OW_STRING_H
#define OW_STRING_H

#include "object.h"

typedef struct OWString_struct {
  char* string; // This is NULL-terminated
  size_t length; // This does NOT count the NULL-byte
} OWString_t;

OWObject_t* OWString_Construct();
int OWString_Set(OWObject_t* this, const char* content, size_t content_size);
int OWString_Append(OWObject_t* this, const char* content, size_t content_size);
#define OWString_GetBuffer(this) ((OWString_t*)OWObject_FindTypeInClass(this, OWID_STRING)->object)->string
#define OWString_GetLength(this) ((OWString_t*)OWObject_FindTypeInClass(this, OWID_STRING)->object)->length
void _OWString_Destroy(OWObject_t* this);
#define OWString_Destroy OWObject_Destroy

#endif
