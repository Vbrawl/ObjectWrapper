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

/**
 * @brief Get the methods of the OWPath_t object.
 *
 * @returns OWPath_t object's methods struct
 */
#define OWPath_Methods(this) (((OWPath_t*)OWObject_FindObjectInClass(this, OWID_PATH))->methods)

/**
 * @brief Construct a path to the CWD
 *
 * Construct a path pointing to the current directory.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWPath_t
 */
SHARED_EXPORT OWO_Path_t* OWPath_ConstructHere();

/**
 * @brief Construct a path
 *
 * @param str The c-string with the path to a directory
 * @param len The size of the c-string
 *
 * Construct a path pointing to the given directory.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWPath_t
 */
SHARED_EXPORT OWO_Path_t* OWPath_Construct(const char* str, size_t len);

/**
 * @brief Construct a path with the given string as `super`
 *
 * Construct a path pointing to the directory got by the super's string buffer.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWPath_t
 */
SHARED_EXPORT OWO_Path_t* OWPath_ConstructWithString(OWO_String_t* string);


/**
 * @brief Check if the path exists
 *
 * @param this The OWPath
 *
 * Check if a path exists in the filesystem
 *
 * @returns true if path exists, false otherwise
 * @memberof OWPath_t
 */
#define OWPath_Exists(this) OWPath_Methods(this).exists(this)

/**
 * @brief Default implementation of OWPath_Exists
 * @memberof OWPath_t
 */
SHARED_EXPORT bool _OWPath_Exists(OWO_Path_t* this);

/**
 * @brief Check if the path exists and is a directory
 *
 * @param this The OWPath
 *
 * Check if a path exists and is a directory
 *
 * @returns true if path exists and is a directory, false otherwise
 * @memberof OWPath_t
 */
#define OWPath_IsDir(this) OWPath_Methods(this).isdir(this)

/**
 * @brief Default implementation of OWPath_IsDir
 * @memberof OWPath_t
 */
SHARED_EXPORT bool _OWPath_IsDir(OWO_Path_t* this);

/**
 * @brief Check if the path exists and is a file
 *
 * @param this The OWPath
 *
 * Check if a path exists and is a file
 *
 * @returns true if path exists and is a file, false otherwise
 * @memberof OWPath_t
 */
#define OWPath_IsFile(this) OWPath_Methods(this).isfile(this)

/**
 * @brief Default implementation of OWPath_IsFile
 * @memberof OWPath_t
 */
SHARED_EXPORT bool _OWPath_IsFile(OWO_Path_t* this);

#endif
