#ifndef OW_VECTOR_H
#define OW_VECTOR_H

/**
 * @file vector.h
 * @brief Vector class
 *
 * This file contains the vector class
 */

#include "object.h"
#include "array.h"

/**
 * @brief OWVector class
 *
 * A C++ vector-like container object/class.
 *
 * @note A vector is capable of storing only OWObject_t classes/objects
 *       but it automatically unreferences them when they are removed
 *       from the vector.
 *
 * @extends OWArray_t
 */
typedef struct {
  /**
   * @brief The size of the vector
   *
   * This is the number of elements inside the vector
   */
  size_t size;

  /**
   * @brief The scaling factor of the vector's buffer size
   *
   * The number of slots the vector increases each time it hits the buffer's limit.
   */
  size_t slot_steps;
} OWVector_t;

/**
 * @brief Vector object type
 *
 * A type for human reference
 */
typedef OWObject_t OWO_Vector_t;

/**
 * @brief Vector object type with a value type
 *
 * A type for human reference
 *
 * An example
 *
 * @code
 * OWO_Typed_Vector_t(OWO_Integer_t*)* vector;
 * @endcode
 *
 * is equivalent to
 *
 * @code
 * OWO_Vector_t* vector;
 * @endcode
 *
 * but the first is more descriptive and there is no confusion
 * about what type is inside the container.
 *
 * @see OWContainer_Type
 */
#define OWO_Typed_Vector_t(type) OWContainer_Type(OWO_Vector_t, type)

/**
 * @brief Construct a vector
 *
 * @param slot_steps The vector's @ref slot_steps
 *
 * Construct an empty vector object.
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWVector_t
 */
OWO_Vector_t* OWVector_Construct(size_t slot_steps);

/**
 * @brief Resize the internal vector's buffer
 *
 * @param this The OWVector
 * @param slots The new number of slots for the vector's internal buffer
 *
 * Resize the internal buffer of the vector, this doesn't affect the actual
 * size of the vector (which is the number of elements stored in it),
 * but simply controls the number of slots in the internal buffer.
 *
 * @see OWArray_Resize
 * @memberof OWVector_t
 */
#define OWVector_Resize(this, slots) OWArray_Resize(this, slots)

/**
 * @brief Insert an item to the vector.
 *
 * @param this The OWVector
 * @param index The position for the new item
 * @param item The item to insert
 *
 * Insert an item to the vector at the given slot.
 *
 * @note index can be a number in the range [0 <= index <= OWVector_t->size]
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @memberof OWVector_t
 */
int OWVector_Insert(OWO_Vector_t* this, size_t index, OWObject_t* item);

/**
 * @brief Add an item to the end of the vector.
 *
 * @param this The OWVector
 * @param item The item to insert
 *
 * Insert an item to the last position in the vector.
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @see OWVector_Insert
 * @memberof OWVector_t
 */
#define OWVector_PushBack(this, item) OWVector_Insert(this, OWVector_GetSize(this), item)

/**
 * @brief Add an item to the start of the vector.
 *
 * @param this The OWVector
 * @param item The item to insert
 *
 * Insert an item to the first position in the vector.
 *
 * @returns 0 on success, a negative value on failure.
 *
 * @see OWVector_Insert
 * @memberof OWVector_t
 */
#define OWVector_PushFront(this, item) OWVector_Insert(this, 0, item)

/**
 * @brief Get the size of the vector.
 *
 * @param this The OWVector
 *
 * Get the number of elements in the vector.
 *
 * @returns The number (size_t) of elements inside the vector.
 * @memberof OWVector_t
 */
#define OWVector_GetSize(this) ((OWVector_t*)OWObject_FindObjectInClass(this, OWID_VECTOR))->size

/**
 * @brief Get an object from the vector.
 *
 * @param this The OWVector
 * @param index The position
 *
 * Get an object from inside the vector in the specified index.
 *
 * @attention The return value is a `NEW` reference to the object.
 *            Make sure to call @ref OWObject_UnRef when you are
 *            done with it.
 *
 * @returns A new reference to the object at the specified index.
 * @memberof OWVector_t
 */
OWObject_t* OWVector_Get(OWO_Vector_t* this, size_t index);

/**
 * @copydoc OWIsEqualCallback_t
 * @memberof OWVector_t
 */
bool OWVector_IsEqual(OWO_Vector_t* this, OWObject_t* other);

/**
 * @brief Remove an object from the vector.
 *
 * @param this The OWVector
 * @param index The position to remove
 *
 * Remove an object from the vector in the specified index.
 *
 * @note The object in the specified index is passed through an @ref OWObject_UnRef
 *       call and will be destroyed if there are no more references to it.
 *
 * @returns 0 on success, a negative value on failure.
 * @memberof OWVector_t
 */
int OWVector_Remove(OWO_Vector_t* this, size_t index);

/**
 * @brief Remove an object and get a reference to it.
 *
 * @param this The OWVector
 * @param index The position to pop
 *
 * Create a new reference to the object and then remove it from the vector
 *
 * @attention The return value is a `NEW` reference to the object.
 *            Make sure to call @ref OWObject_UnRef when you are
 *            done with it.
 *
 * @returns A new reference to the object at the specified index.
 * @memberof OWVector_t
 */
OWObject_t* OWVector_Pop(OWO_Vector_t* this, size_t index);

/**
 * @brief Call @ref OWVector_Pop for the last item in the vector
 *
 * @param this The OWVector
 *
 * Pop the last item in the vector
 *
 * @see OWVector_Pop
 * @memberof OWVector_t
 */
#define OWVector_PopBack(this) OWVector_Pop(this, OWVector_GetSize(this) - 1)

/**
 * @brief Call @ref OWVector_Pop for the first item in the vector
 *
 * @param this The OWVector
 *
 * Pop the first item in the vector
 *
 * @see OWVector_Pop
 * @memberof OWVector_t
 */
#define OWVector_PopFront(this) OWVector_Pop(this, 0)

/**
 * @copydoc OWObject_Destroy
 * @memberof OWVector_t
 */
#define OWVector_Destroy OWObject_Destroy


#endif
