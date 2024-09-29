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
struct _OWPath_Methods {};


/**
 * @brief OWPath class
 *
 * Represents a location to the file system.
 *
 * @extends OWString_t
 */
SHARED_EXPORT typedef struct {

} OWPath_t;


OWO_Path_t* OWPath_ConstructHere();
OWO_Path_t* OWPath_Construct(const char* str, size_t len);
OWO_Path_t* OWPath_ConstructWithString(OWO_String_t* string);


bool OWPath_Exists(OWO_Path_t* this);
bool OWPath_IsDir(OWO_Path_t* this);
bool OWPath_IsFile(OWO_Path_t* this);

#endif
