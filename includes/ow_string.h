#ifndef OW_STRING_H
#define OW_STRING_H

#include "object.h"
#include "array.h"
#include <string.h>
#include <stdbool.h>

/**
 * @file ow_string.h
 * @brief String class
 *
 * This file contains the string class
 */

/**
 * @brief OWString class
 *
 * Represents a string object/class.
 *
 * @extends OWArray_t
 */
typedef struct {
  size_t size; // This does NOT count the NULL-byte
} OWString_t;

/**
 * @brief String object type
 *
 * Create a type for human reference
 */
typedef OWObject_t OWO_String_t;

/**
 * @brief Construct a string
 *
 * @param content The initial content of the string
 * @param content_size The size of the initial content of the string (not counting the NULL-byte)
 *
 * Construct a string with the given content. The content_size can be used to trim the string.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 * @memberof OWString_t
 */
OWO_String_t* OWString_Construct(const char* content, size_t content_size);

/**
 * @brief Construct an empty string
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWString_t
 */
#define OWString_ConstructEmpty() OWString_Construct(NULL, 0)

/**
 * @brief User-Friendly string constructor
 *
 * @param content The initial content of the string
 *
 * Construct a string with the given content.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWString_t
 */
#define OWString_ConstructSimple(content) OWString_Construct(content, strlen(content))

/**
 * @brief Clone an OWString object
 *
 * @param this The OWString to clone.
 *
 * Create a complete copy of an OWString object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWString_t
 */
#define OWString_Clone(this) OWString_Construct(OWString_GetBuffer(this), OWString_GetSize(this))

/**
 * @brief Set/Replace the contents of a string
 *
 * @param this The OWString which contents will be set/replaced
 * @param content The content that will be placed in OWString's buffer
 * @param content_size The number of bytes to copy from content to OWString's buffer (not counting the NULL-byte)
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
int OWString_Set(OWO_String_t* this, const char* content, size_t content_size);

/**
 * @brief A simple way to set a string's contents
 *
 * @param this The OWString which contents will be set/replaced
 * @param content The content that will be placed in OWString's buffer
 *
 * This macro automatically finds the string length using strlen().
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
#define OWString_SetSimple(this, content) OWString_Set(this, content, strlen(content))

/**
 * @brief Set/Replace the contents of a string to the contents of another string
 *
 * @param this The OWString which contents will be set/replaced
 * @param other The OWString which contents will be copied over to `this`
 *
 * This macro automatically finds the content and it's length.
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
#define OWString_SetOWString(this, other) OWString_Set(this, OWString_GetBuffer(other), OWString_GetSize(other))

/**
 * @brief Add content to an OWString
 *
 * @param this The OWString wihch contents will be expanded
 * @param content The content to add to OWString's buffer
 * @param content_size The number of bytes to add from content to OWString's buffer (not counting the NULL-byte)
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
int OWString_Append(OWO_String_t* this, const char* content, size_t content_size);

/**
 * @brief A simple way to add content to an OWString
 *
 * @param this The OWString which contents will be expanded
 * @param content The content to add to OWString's buffer
 *
 * This macro automatically finds the content's size using strlen().
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
#define OWString_AppendSimple(this, content) OWString_Append(this, content, strlen(content))

/**
 * @brief Add contents of an OWString to another OWString
 *
 * @param this The OWString which contents will be expanded
 * @param other The OWString which contents will be added to `this`
 *
 * This macro automatically finds the content and it's length.
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWString_t
 */
#define OWString_AppendOWString(this, other) OWString_Append(this, OWString_GetBuffer(other), OWString_GetSize(other))

/**
 * @brief Compare an OWString with a c-string
 *
 * @param this The OWString which contents will be compared to the c-string
 * @param other The c-string which will be compared to the contents of `this`
 * @param other_size The number of bytes of the c-string that will be compared (not counting the NULL-byte)
 *
 * Examples
 *
 * @code{.c}
 * OWString_Compare("Hello World", "Hello World");  //  0
 * OWString_Compare("Hello Worle", "Hello World");  //  1
 * OWString_Compare("Hello World", "Hello Worle");  // -1
 * OWString_Compare("Hello World!", "Hello World"); //  33
 * OWString_Compare("Hello World", "Hello World!"); // -33
 * @endcode
 *
 * @returns 0 on equality, the difference of the first differing character on non-equality.
 *
 * @memberof OWString_t
 */
int OWString_Compare(OWO_String_t* this, const char* other, size_t other_size);

/**
 * @brief A simple way to use compare an OWString to a c-string
 *
 * @see OWString_Compare
 *
 * @param this The OWString which contents will be compared to the c-string
 * @param other The c-string which will be compared to the contents of `this`
 *
 * This macro automatically finds the content's length.
 *
 * @returns 0 on equality, the difference of the first differing character on non-equality.
 *
 * @memberof OWString_t
 */
#define OWString_CompareSimple(this, other) OWString_Compare(this, other, strlen(other))

/**
 * @brief Compare an OWString to another OWString
 *
 * @see OWString_Compare
 *
 * @param this The OWString which contents will be compared to the other OWString
 * @param other The other OWString which contents will be compared to `this`
 *
 * This macro automatically finds the content and it's length.
 *
 * @returns 0 on equality, the difference of the first differing character on non-equality.
 *
 * @memberof OWString_t
 */
#define OWString_CompareOWString(this, other) OWString_Compare(this, OWString_GetBuffer(other), OWString_GetSize(other))

/**
 * @copydoc OWIsEqualCallback_t
 * @memberof OWString_t
 */
bool OWString_IsEqual(OWO_String_t* this, OWObject_t* other);

/**
 * @brief Get a substring from an OWString's content
 *
 * @param this The OWString which contents will be used to create the substring
 * @param start The starting position of the substring
 * @param size The number of bytes to copy to the substring
 *
 * @returns An OWString with the selected contents.
 *
 * @memberof OWString_t
 */
OWO_String_t* OWString_SubString(OWO_String_t* this, size_t start, size_t size);

/**
 * @brief Find a substring in the OWString's content
 *
 * @param this The OWString which contents will be searched
 * @param sub The contents to search for
 * @param sub_size The length of the contents to search for
 *
 * Find the position of a substring in a string.
 *
 * @returns The offset in which the sub-string was found or -1 if substring was not found.
 */
size_t OWString_FindStr(OWO_String_t* this, const char* sub, size_t sub_size);

/**
 * @brief Simple way to call @ref OWString_FindStr
 *
 * @param this The OWString which contents will be searched
 * @param sub The contents to search for
 *
 * This macro automatically finds the content's length.
 *
 * @returns The offset in which the sub-string was found or -1 if substring was not found.
 * @memberof OWString_t
 */
#define OWString_FindStrSimple(this, sub) OWString_FindStr(this, sub, strlen(sub))

/**
 * @brief Call @ref OWString_FindStr for @ref OWString_t objects
 *
 * @param this The OWString which will be searched
 * @param other The OWString to search for
 *
 * This macro automatically finds the content and it's length.
 *
 * @returns The offset in which the sub-string was found or -1 if substring was not found.
 * @memberof OWString_t
 */
#define OWString_FindStrOWString(this, other) OWString_FindStr(this, OWString_GetBuffer(other), OWString_GetSize(other))

/**
 * @brief Get the internal buffer of the string
 *
 * @param this The OWString
 *
 * @returns A c-string (aka `char*`, note the absense of `const`)
 *
 * @memberof OWString_t
 */
#define OWString_GetBuffer(this) ((char*)OWArray_GetBuffer(this))

/**
 * @brief Get the string's length
 *
 * @param this The OWString
 *
 * @returns The length of the string (size_t)
 *
 * @memberof OWString_t
 */
#define OWString_GetSize(this) ((OWString_t*)OWObject_FindObjectInClass(this, OWID_STRING))->size

/**
 * @copydoc OWString_GetSize
 * @memberof OWString_t
 */
#define OWString_GetLength(this) OWString_GetSize(this)

/**
 * @brief Resize the string's buffer
 *
 * @param this The OWString
 * @param size The new size of the string (including the NULL-byte)
 *
 * Resize the internal buffer of the string, this doesn't affect the actual size of the contents
 * it can be used to control the memory used by OWString but not the length of the string.
 *
 * @note `size` needs to include the NULL-byte.
 *
 * @warning Resizing the string to something less than the content's length will cause
 *          the implementation will break. There are ways to get away with it but
 *          it's not recommended. Any calls with a `size` value less than the content's
 *          length should be considered as `undefined behaviour`.
 *
 * @see OWArray_Resize
 * @memberof OWString_t
 */
#define OWString_Resize(this, size) OWArray_Resize(this, size)

/**
 * @copydoc OWObject_Destroy
 * @memberof OWString_t
 */
#define OWString_Destroy(this) OWObject_Destroy(this)

#endif
