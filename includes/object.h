#ifndef OW_CLASS_H
#define OW_CLASS_H

/**
 * @file object.h
 * @brief Basic object implementation
 *
 * This file is the core of the library.
 */

#include <stddef.h>
#include "object_identifiers.h"

/**
 * @brief Register a new OWID for a class
 *
 * @param cls The class name (definition is not needed)
 * @param id The number that identifies the class
 *
 * This macro is used to generate a new OWID for a class.
 */
#define OWID_Register(cls, id) \
  enum { OWID_##cls = id };

/**
 * @brief Used to define a container type and it's subtype
 *
 * @param container The type of the container
 * @param ... The type to be stored inside the container
 *
 * This is a macro that can be used to define a container and it's subtype.
 * It's more or less equivalent to C++'s template's parameters but doesn't
 * actually check the subtype.
 *
 * An example
 *
 * @code{.cpp}
 * std::vector<OWO_Integer_t*> numbers;
 * @endcode
 *
 * is equivalent with
 *
 * @code{.c}
 * // Note the "*" after the parenthesis
 * OWContainer_Type(OWO_Array_t, OWO_Integer_t*)* numbers;
 * @endcode
 *
 * which is equivalent to
 *
 * @code{.c}
 * OWO_Array_t* numbers;
 * @endcode
 */
#define OWContainer_Type(container, ...) container

struct OWObject_struct;

/**
 * @brief The object's destructor function type
 *
 * @param this The object being destroyed
 *
 * The destructor needs to make sure everything inside the object is deallocated.
 */
typedef void(OWDestroyCallback_t)(struct OWObject_struct* this);

struct OWObject_struct {

  /**
   * @brief Reference to the super/parent of the current object
   *
   * A pointer to the super class/object.
   * If there is no super class/object this points to NULL.
   *
   * @memberof OWObject_t
   */
  struct OWObject_struct* super;

  /**
   * @brief Data of the object
   *
   * A variadic pointer referencing the data of the current object.
   *
   * @memberof OWObject_t
   */
  void* object;

  /**
   * @brief The destructor of the class/object.
   *
   * This is not a NULL pointer, it's getting called when the object is to be destroyed.
   *
   * @memberof OWObject_t
   */
  OWDestroyCallback_t* destroy_callback;

  /**
   * @brief The object's reference counter
   *
   * This holds the number of references to the current object.
   * When this hits 0 the object is automatically destroyed. (Sort of a garbage collector)
   *
   * @memberof OWObject_t
   */
  _Atomic int reference_count;

  /**
   * The object's type
   *
   * @memberof OWObject_t
   */
  OWID type;
}

/**
 * @class OWObject_t
 * @brief The ObjectWrapper
 *
 * Container allowing variadic data to be stored in it.
 * Capable of holding a reference to the parent of the current class/object.
 */
typedef struct OWObject_struct OWObject_t;;

/**
 * @brief Easier object constructor
 *
 * @param cls The class to construct
 * @param destroy_callback The function to be called when the object is to be destroyed
 * @param super The super/parent object
 *
 * A macro to easily call the OWObject_t's constructor
 *
 * @returns A pointer to the constructed `OWObject_t` instance or `NULL` on failure.
 * @memberof OWObject_t
 */
#define OWObject_Construct(cls, destroy_callback, super) _OWObject_Construct(sizeof(cls), OWID_##cls, destroy_callback, super);

/**
 * @brief Easy access to the super/parent object
 *
 * @param type The type of the super/parent object's data
 * @param cls The current object
 *
 * @returns A pointer to the parent `OWObject_t` instance or `NULL` if there is no parent.
 * @memberof OWObject_t
 */
#define OWObject_Super(type, cls) ((type*)cls->super->object)

/**
 * @brief The actual OWObject_t's constructor
 *
 * @param size The size needed for the object's data
 * @param type The type of the object
 * @param destroy_callback The destructor of the object
 * @param super The super/parent object
 *
 * Construct an OWObject_t object and return a reference to it.
 *
 * @returns A pointer to the constructed `OWObject_t` instance or `NULL` on failure.
 * @memberof OWObject_t
 */
OWObject_t* _OWObject_Construct(size_t size, OWID type, OWDestroyCallback_t* destroy_callback, OWObject_t* super);

/**
 * @brief Find an object in inheritance chain
 *
 * @param this The object to search it's inheritance chain
 * @param type The type to find in the inheritance chain
 *
 * Find an object in the inheritance chain using it's type.
 *
 * @returns A pointer to the discovered `OWObject_t` instance or `NULL` on failure.
 * @memberof OWObject_t
 */
OWObject_t* OWObject_FindTypeInClass(OWObject_t* this, OWID type);

/**
 * @brief Find an object's data in the inheritance chain
 *
 * @param this The object to search it's inheritance chain
 * @param type The type to find in the inheritance chain
 *
 * Find an object in the inheritance chain using it's type and return it's data.
 *
 * @returns A pointer to the data of the discovered `OWObject_t` instance (which is of unknown/variadic type) or `NULL` on failure.
 * @memberof OWObject_t
 */
void* OWObject_FindObjectInClass(OWObject_t* this, OWID type);

/**
 * @brief Get a new reference to an object.
 *
 * @param this The object to get a reference to.
 *
 * Create a reference to keep an object alive.
 *
 * @returns A pointer pointing to the same address as `this`.
 * @memberof OWObject_t
 */
OWObject_t* OWObject_Ref(OWObject_t* this);

/**
 * @brief Destroy a reference to an object.
 *
 * @param this The reference to the object to delete.
 *
 * When there are no more references to the object this will automatically destroy it.
 *
 * @memberof OWObject_t
 */
void OWObject_UnRef(OWObject_t* this);

/**
 * @brief Get the number of references to the object.
 *
 * @param this The object to get the reference count of
 *
 * This macro is used to easily access the reference_count.
 *
 * @memberof OWObject_t
 */
#define OWObject_GetRefCount(this) this->reference_count

/**
 * @brief Destroy an object
 *
 * @param this The object to destroy.
 *
 * Manually destroy an object. All references to the object are invalidated
 * and trying to access them is undefined behaviour.
 *
 * @memberof OWObject_t
 */
void OWObject_Destroy(OWObject_t* this);



#endif
