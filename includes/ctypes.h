#ifndef OW_CTYPES_H
#define OW_CTYPES_H

/**
 * @file ctypes.h
 * @brief Classes for basic c-types
 *
 * This file contains classes for basic C types like int, char, bool
 */

#include "object.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @class OWCType_t
 * @brief Container for C-Types
 *
 * A variadic container for C types
 *
 * @note This class doesn't have a constructor but all classes that extend it should have.
 *
 * @extends OWObject_t
 */
SHARED_EXPORT typedef struct {
  void* value;
  size_t size;
} OWCType_t;

/**
 * @brief CType variadic object type
 *
 * A type for human reference
 */
SHARED_EXPORT typedef OWObject_t OWO_CType_t;

#define OWCType_UnWrap(c_type, this) (*(c_type*)((OWCType_t*)OWObject_FindObjectInClass(this, OWID_CTYPE))->value)


/**
 * @class OWInteger_t
 * @brief Integer object type
 *
 * A type for human reference
 *
 * @extends OWCType_t
 */
SHARED_EXPORT typedef OWObject_t OWO_Integer_t;

/**
 * @brief Construct an integer
 *
 * @param object The integer to store in the object
 *
 * Store an integer inside the object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWInteger_t
 */
SHARED_EXPORT OWO_Integer_t* OWInteger_Construct(int object);

/**
 * @brief Extract an OWInteger
 *
 * @param this The OWInteger
 *
 * Extract the value of an OWInteger to a C integer
 *
 * @returns An integer (int) with the value inside of the passed in object.
 * @memberof OWInteger_t
 */
#define OWInteger_UnWrap(this) OWCType_UnWrap(int, this)


/**
 * @class OWUnsignedInteger8_t
 * @brief Unsigned 8-bit integer object type
 *
 * A type for human reference
 *
 * @extends OWCType_t
 */
SHARED_EXPORT typedef OWObject_t OWO_UnsignedInteger8_t;

/**
 * @brief Construct an unsigned 8-bit integer
 *
 * @param object The uint8_t to store in the object
 *
 * Store an unsigned 8-bit integer inside the object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWUnsignedInteger8_t
 */
SHARED_EXPORT OWO_UnsignedInteger8_t* OWUnsignedInteger8_Construct(uint8_t object);

/**
 * @brief Extract an OWUnsignedInteger8_t
 *
 * @param this The OWUnsignedInteger8_t
 *
 * Extract the value of an OWInteger to a C unsigned 8-bit integer
 *
 * @returns An unsigned 8-bit integer (uint8_t) with the value inside of the passed in object.
 * @memberof OWUnsignedInteger8_t
 */
#define OWUnsignedInteger8_UnWrap(this) OWCType_UnWrap(uint8_t, this)


/**
 * @class OWCharacter_t
 * @brief Character object type
 *
 * A type for human reference
 *
 * @extends OWCType_t
 */
SHARED_EXPORT typedef OWObject_t OWO_Character_t;

/**
 * @brief Construct a character
 *
 * @param object The character to store in the object
 *
 * Store a character inside the object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWCharacter_t
 */
SHARED_EXPORT OWO_Character_t* OWCharacter_Construct(char object);

/**
 * @brief Extract an OWCharacter
 *
 * @param this The OWCharacter
 *
 * Extract the value of an OWCharacter to a C character
 *
 * @returns A character (char) with the value inside of the passed in object.
 * @memberof OWCharacter_t
 */
#define OWCharacter_UnWrap(this) OWCType_UnWrap(char, this)


/**
 * @class OWBoolean_t
 * @brief Boolean object type
 *
 * A type for human reference
 *
 * @extends OWCType_t
 */
SHARED_EXPORT typedef OWObject_t OWO_Boolean_t;

/**
 * @brief Construct a boolean
 *
 * @param object The boolean to store in the object
 *
 * Store a boolean inside the object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWBoolean_t
 */
SHARED_EXPORT OWO_Boolean_t* OWBoolean_Construct(bool object);

/**
 * @brief Extract an OWBoolean
 *
 * @param this The OWBoolean
 *
 * Extract the value of an OWBoolean to a C boolean
 *
 * @returns A boolean (bool) with the value inside of the passed in object.
 * @memberof OWBoolean_t
 */
#define OWBoolean_UnWrap(this) OWCType_UnWrap(bool, this)



#endif
