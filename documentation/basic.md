
# Basic Info

The ``OWObject_t`` is an object structure that holds information about an object.

Every object is supposed to be inside a ``OWObject_t`` and this in-turn holds the
address to the structure of the object.


To access the object inside the ``OWObject_t`` we simply need to do ``(type*)instance->object``.



# TypeDefs

Each object should have at least 1 typedef, recommended 2.

Minimal object structure:
```
OWID_Register(MyClass_t, OWID_USER_DEFINED + 1);
typedef struct MyClass_struct {
  int some_integer;
  char some_char;
} MyClass_t;
```

The minimal object structure allows you to use the OWID_Register
preprocessor macro to define a new object type.

It is possible to define an OWID without the OWID_Register,
which is how the library defines object types, but that may
be less user friendly.


Recommended object structure:
```
OWID_Register(MyClass_t, OWID_USER_DEFINED + 1);
typedef struct MyClass_struct {
  int some_integer;
  char some_char;
} MyClass_t;

typedef OWObject_t OWO_MyClass_t;
```

The recommended object structure allows you to use ``OWO_MyClass_t``
as the type for parameters and variables and thus have a more distinguishable way
to know if something is supposed to be a MyClass_t object or a Vector_t object