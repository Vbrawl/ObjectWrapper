#ifndef COW_SAY_H
#define COW_SAY_H

#include <ObjectWrapper/object.h>
#include <ObjectWrapper/ow_string.h>

// We define an extern OWID for our object
extern OWID OWID_CowSay_t;
typedef struct {
  OWO_String_t* name;
} CowSay_t;
typedef OWObject_t O_CowSay_t;


O_CowSay_t* CowSay_Construct(OWO_String_t* name);
void CowSay_SayHi(O_CowSay_t* this);

#endif
