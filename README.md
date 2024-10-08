
# Description

This project is a class/object system for the C language.

With this library you can implement classes and sub-classes, you can achieve inheritance
and more in C.

# Installation

```
cmake -B build
cd build
make
sudo make install
```

In some systems you may need to run `sudo ldconfig`

# Examples

There are some examples in the `examples` directory

## Important

For creating shared libraries in a compact and portable manner visit the `shared_library` example

# Linking to library

To make projects that use this library you need to link against
the shared library `libobjectwrapper`

Example in CMake:

```
link_libraries(objectwrapper)
```

# Source Code Style

Some rules for the source code:

* functions **PascalCase**
* classes/types **PascalCase + _struct/_t postfix**
* methods **ClassName prefix + PascalCase**
* constants **SCREAMING_SNAKE_CASE**
* variables **snake_case**
* globals **SCREAMING_SNAKE_CASE + _g postfix**
* file names **snake_case**

# License

This project is licensed under the MIT license
