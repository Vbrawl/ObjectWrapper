#ifndef OW_ARRAY_H
#define OW_ARRAY_H

/**
 * @file array.h
 * @brief OWArray object
 *
 * This file contains the OWArray object
 */

#include "object.h"

/**
 * @brief OWArray class
 *
 * Represents an array object/class.
 *
 * @extends OWObject_t
 */
typedef struct {
  /**
   * @brief Variadic array for the object's stored data
   *
   * This variadic c-array is the main container of the object.
   *
   * The array's length can be retrieved from @ref slots and @ref OWArray_GetSlots
   */
  void* array;

  /**
   * @brief The array's length
   *
   * This is the number of slots in the array.
   *
   * @see slot_size
   */
  size_t slots;

  /**
   * @brief The size of each slot
   *
   * This is the size of a single slot.
   *
   * To get the memory allocated by OWArray you need to multiply
   * @ref slots and @ref slot_size
   */
  size_t slot_size;
} OWArray_t;

/**
 * @brief Array object type
 *
 * A type for human reference
 */
typedef OWObject_t OWO_Array_t;

/**
 * @brief Array object type with a value type
 *
 * A type for human reference
 *
 * An example
 *
 * @code
 * OWO_Typed_Array_t(OWO_Integer_t*)* array;
 * @endcode
 *
 * is equivalent to
 *
 * @code
 * OWO_Array_t* array;
 * @endcode
 *
 * but the first is more descriptive and there is no confusion
 * about what type is inside the container.
 *
 * @see OWContainer_Type
 */
#define OWO_Typed_Array_t(type) OWContainer_Type(OWO_Array_t, type)

/**
 * @brief Construct an array
 *
 * @param slot_size The size of each slot in bytes
 * @param slots The number of slots to allocate
 *
 * Construct an array of size `slots` where each slot can store up to `slot_size` bytes
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWArray_t
 */
OWO_Array_t* OWArray_Construct(size_t slot_size, size_t slots);

/**
 * @brief Resize the array
 *
 * @param this The OWArray to resize
 * @param slots The new number of slots
 *
 * Resize the array to have the given number of slots.
 *
 * @note Resizing the array doesn't move any data so it's possible
 *       for memory leaks to be caused. Use with care.
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWArray_t
 */
int OWArray_Resize(OWO_Array_t* this, size_t slots);

/**
 * @copydoc OWIsEqualCallback_t
 * @memberof OWArray_t
 */
bool OWArray_IsEqual(OWO_Array_t* this, OWObject_t* other);

/**
 * @brief Access a slot in the array
 *
 * @param cast_type The type of the objects in the array
 * @param this The array to access
 * @param index The index of the slot to access
 *
 * Access the value of the given slot, this macro can be used
 * for reading or writing to the slot.
 *
 * @memberof OWArray_t
 */
#define OWArray_At(cast_type, this, index) ((cast_type*)((OWArray_t*)OWObject_FindObjectInClass(this, OWID_ARRAY))->array)[index]

/**
 * @brief Access the internal array buffer
 *
 * @param this The array
 *
 * Access the internal buffer of `this`.
 *
 * @returns A void pointer (void*) which points to the start of the internal buffer.
 *
 * @memberof OWArray_t
 */
#define OWArray_GetBuffer(this) ((OWArray_t*)OWObject_FindObjectInClass(this, OWID_ARRAY))->array

/**
 * @brief The number of slots of the array
 *
 * @param this The array
 *
 * Get the number of slots in the array
 *
 * @returns The number (size_t) of slots in the array.
 *
 * @memberof OWArray_t
 */
#define OWArray_GetSlots(this) ((OWArray_t*)OWObject_FindObjectInClass(this, OWID_ARRAY))->slots

/**
 * @copydoc OWObject_Destroy
 * @memberof OWArray_t
 */
#define OWArray_Destroy OWObject_Destroy

#endif
