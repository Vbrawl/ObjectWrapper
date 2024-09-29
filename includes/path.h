#ifndef OW_PATH_H
#define OW_PATH_H

/**
 * @file path.h
 * @brief OWPath object
 *
 * This file contains OWPath object
 */

#include "object.h"
#include "ow_string.h"
#include <stdbool.h>

/**
 * @brief Path object type
 *
 * A type for human reference
 */
SHARED_EXPORT typedef OWO_String_t OWO_Path_t;

/**
 * A structure to hold all object's virtual methods
 */
struct _OWPath_Methods {
  bool(*exists)(OWO_Path_t* this);
  bool(*isdir)(OWO_Path_t* this);
  bool(*isfile)(OWO_Path_t* this);
};


/**
 * @brief OWPath class
 *
 * Represents a location to the file system.
 *
 * @extends OWString_t
 */
SHARED_EXPORT typedef struct {
  struct _OWPath_Methods methods;
} OWPath_t;

#define OWPath_Methods(this) (((OWPath_t*)OWObject_FindObjectInClass(this, OWID_PATH))->methods)

SHARED_EXPORT OWO_Path_t* OWPath_ConstructHere();
SHARED_EXPORT OWO_Path_t* OWPath_Construct(const char* str, size_t len);
SHARED_EXPORT OWO_Path_t* OWPath_ConstructWithString(OWO_String_t* string);


#define OWPath_Exists(this) OWPath_Methods(this).exists(this)
SHARED_EXPORT bool _OWPath_Exists(OWO_Path_t* this);
#define OWPath_IsDir(this) OWPath_Methods(this).isdir(this)
SHARED_EXPORT bool _OWPath_IsDir(OWO_Path_t* this);
#define OWPath_IsFile(this) OWPath_Methods(this).isfile(this)
SHARED_EXPORT bool _OWPath_IsFile(OWO_Path_t* this);

#endif
