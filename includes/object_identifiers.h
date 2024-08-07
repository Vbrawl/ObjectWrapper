#ifndef OW_OBJECT_IDENTIFIERS_H
#define OW_OBJECT_IDENTIFIERS_H

// Type for OWID_* constants
typedef int OWID;
enum {
  OWID_UNDEFINED = 0,
  OWID_VECTOR = 1,
  OWID_STRING = 2,
  OWID_ARRAY = 3,
  OWID_MAP = 4,

  OWID_INTEGER = 5,
  OWID_CHARACTER = 6,
  OWID_BOOLEAN = 7,

  OWID_USER_DEFINED = 1000
};


#endif

