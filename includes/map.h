#ifndef OW_MAP_H
#define OW_MAP_H

/**
 * @file map.h
 * @brief Map class
 *
 * This file contains the map class
 */

#include "object.h"
#include "ow_string.h"
#include "vector.h"

/**
 * @brief Map object type
 *
 * A type for human reference
 */
typedef OWObject_t OWO_Map_t;


struct _OWMap_Methods {
  int(*set)(OWO_Map_t* this, OWObject_t* key, OWObject_t* item);
  int(*unset)(OWO_Map_t* this, OWObject_t* key);
  size_t(*find_entry)(OWO_Map_t* this, OWObject_t* key);
  OWObject_t*(*get)(OWO_Map_t* this, OWObject_t* key);
};


/**
 * @brief OWMap class
 *
 * Represents a map object/class.
 *
 * @note Can only hold references to OWObject_t objects and unreferences
 *       when they are removed from the map
 */
typedef struct {
  /**
   * @brief Key vector
   *
   * A vector holding all keys of the object
   */
  OWO_Vector_t* keys;

  /**
   * @brief Value vector
   *
   * A vector holding all values of the object
   */
  OWO_Vector_t* values;

  /**
   * @brief Methods
   */
  struct _OWMap_Methods methods;
} OWMap_t;

/**
 * @brief Map object type with a value type
 *
 * A type for human reference
 *
 * An example
 *
 * @code
 * OWO_Typed_Map_t(OWO_Integer_t*)* map;
 * @endcode
 *
 * is equivalent to
 *
 * @code
 * OWO_Map_t* map;
 * @endcode
 *
 * but the first is more descriptive and there is no confusion
 * about what type is inside the container.
 *
 * @see OWContainer_Type
 */
#define OWO_Typed_Map_t(key_type, value_type) OWContainer_Type(OWO_Map_t, key_type, value_type)

/**
 * @brief Construct a map
 *
 * @param slot_steps The slot steps for auto-resizing (see @ref OWVector_t::slot_steps)
 *
 * @returns A pointer to the object instance that was created or `NULL` on failure.
 *
 * @memberof OWMap_t
 */
OWO_Map_t* OWMap_Construct(size_t slot_steps);

/**
 * @brief Get the methods struct of the OWMap_t object
 *
 * @returns The OWMap_t object's methods struct.
 * @memberof OWMap_t
 */
#define OWMap_Methods(this) ((OWMap_t*)OWObject_FindObjectInClass(this, OWID_MAP))->methods

/**
 * @brief Set a key in the map
 *
 * @param this The OWMap
 * @param key The key
 * @param item The value for the key
 *
 * Add a new entry or replace an existing one with the specified key and value
 *
 * @note A new reference of both the key and the value is created.
 *
 * @returns 0 on success, a negative value on failure.
 * @memberof OWMap_t
 */
#define OWMap_Set(this, key, item) OWMap_Methods(this).set(this, key, item)

/**
 * @brief Default implementation of OWMap_Set
 * @memberof OWMap_t
 */
int _OWMap_Set(OWO_Map_t* this, OWObject_t* key, OWObject_t* item);

/**
 * @brief Unset a key in the map
 *
 * @param this The OWMap
 * @param key The key
 *
 * Clear an entry with the specified key from the map.
 *
 * @note Both the key and the value that are stored
 *       in the internal buffers of the map are passed
 *       through an @ref OWObject_t::OWObject_UnRef call and they might
 *       be destroyed if there are no more references to them.
 *
 * @returns 0 on success, a negative value on failure.
 * @memberof OWMap_t
 */
#define OWMap_UnSet(this, key) OWMap_Methods(this).unset(this, key)

/**
 * @brief Default implementation of OWMap_UnSet
 * @memberof OWMap_t
 */
int _OWMap_UnSet(OWO_Map_t* this, OWObject_t* key);


/**
 * @brief Find the index of an entry in the underlying buffers vector
 *
 * @param this The OWMap
 * @param key The key to search for
 *
 * Find the index of an entry
 *
 * @returns The index of the entry or -1 on failure
 * @memberof OWMap_t
 */
#define OWMap_FindEntry(this, key) OWMap_Methods(this).find_entry(this, key)

/**
 * @brief Default implementation of OWMap_FindEntry
 * @memberof OWMap_t
 */
size_t _OWMap_FindEntry(OWO_Map_t* this, OWObject_t* key);

/**
 * @brief Get the value of a key
 *
 * @param this The OWMap
 * @param key The key to use
 *
 * Get a new reference to the value pointed to by the specified key.
 *
 * @attention A new reference to the value is returned, make sure to
 *            call @ref OWObject_t::OWObject_UnRef when you are done with it.
 *
 * @returns A new reference to the value object or `NULL` if the key was not found in the map.
 * @memberof OWMap_t
 */
#define OWMap_Get(this, key) OWMap_Methods(this).get(this, key)

/**
 * @brief Default implementation of OWMap_Get
 * @memberof OWMap_t
 */
OWObject_t* _OWMap_Get(OWO_Map_t* this, OWObject_t* key);

/**
 * @brief Get the vector of keys of the object
 *
 * @param this The OWMap
 *
 * Get the internal vector of keys.
 *
 * @warning Modifying the vector will damage the map object and will result in undefined behaviour.
 *          The resulting OWVector should be used as read-only.
 *
 * @returns A reference to the internal key vector or NULL on failure.
 * @memberof OWMap_t
 */
#define OWMap_GetKeyVector(this) OWObject_Ref(((OWMap_t*)OWObject_FindObjectInClass(this, OWID_MAP))->keys)

/**
 * @copydoc OWIsEqualCallback_t
 * @memberof OWMap_t
 */
#define OWMap_IsEqual(this, other) OWObject_IsEqual(this, other)

/**
 * @brief Default implementation of OWMap_IsEqual
 * @memberof OWMap_t
 */
bool _OWMap_IsEqual(OWO_Map_t* this, OWObject_t* other);

/**
 * @brief Get the size of the map
 *
 * @param this The OWMap
 *
 * @returns The number (size_t) of the entries in the map.
 * @memberof OWMap_t
 */
#define OWMap_GetSize(this) OWVector_GetSize(((OWMap_t*)OWObject_FindObjectInClass(this, OWID_MAP))->keys)

/**
 * @copydoc OWObject_Destroy
 * @memberof OWMap_t
 */
#define OWMap_Destroy OWObject_Destroy

#endif
