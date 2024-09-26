#ifndef OW_OBJECT_IDENTIFIERS_H
#define OW_OBJECT_IDENTIFIERS_H

#ifndef SHARED_EXPORT
  #ifdef _WIN32
    #define SHARED_EXPORT __declspec(dllexport)
  #else
    #define SHARED_EXPORT
  #endif
#endif

/**
 * @file object_identifiers.h
 * @brief Object Wrapper Identifier
 *
 * This file contains the basic OWIDs of the library
 */

/**
 * @brief Object Wrapper Identifier
 *
 * This is the type for the object identifiers
 *
 * All values for this type should have the `OWID_` prefix.
 */
SHARED_EXPORT typedef int OWID;
enum {
  OWID_UNDEFINED = 0,
  OWID_VECTOR = 1,
  OWID_STRING = 2,
  OWID_ARRAY = 3,
  OWID_MAP = 4,

  OWID_CTYPE = 5,

  OWID_USER_DEFINED = 1000
};


#endif

