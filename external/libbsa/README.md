# Libbsa

[![Build Status](https://travis-ci.org/WrinklyNinja/libbsa.svg?branch=master)](https://travis-ci.org/WrinklyNinja/libbsa)

Libbsa is a free software library for reading and writing BSA files.

## Build Instructions

Libbsa uses [CMake](http://cmake.org) to generate build files. Instructions for Windows are given below.

### Requirements

* [Boost](http://www.boost.org) v1.55+ Filesystem, Iostreams and Locale libraries
* [Google Test](https://github.com/google/googletest): Required to build libloadorder's tests, but not the library itself. Tested with v1.7.0.
* [zlib](http://zlib.net) v1.2.8

The Google Test and zlib dependencies are automatically managed by CMake, but Boost must be obtained separately.

### Windows

#### Boost

```
bootstrap.bat
b2 toolset=msvc threadapi=win32 link=static runtime-link=static variant=release address-model=32 --with-iostreams --with-filesystem --with-locale --with-system
```

`link`, `runtime-link` and `address-model` can all be modified if shared linking or 64 bit builds are desired. Libloadorder uses statically-linked Boost libraries by default: to change this, edit [CMakeLists.txt](CMakeLists.txt).

#### Libbsa

Libbsa uses the following CMake variables to set build parameters:

Parameter | Values | Description
----------|--------|------------
`BUILD_SHARED_LIBS` | `ON`, `OFF` | Whether or not to build a shared libbsa. Defaults to `ON`.
`PROJECT_STATIC_RUNTIME` | `ON`, `OFF` | Whether to link the C++ runtime statically or not. This also affects the Boost libraries used. Defaults to `ON`.

You may also need to define `BOOST_ROOT` if CMake can't find Boost.

1. Set CMake up so that it builds the binaries in the `build` subdirectory of the libbsa folder.
2. Define any necessary parameters.
3. Configure CMake, then generate a build system for Visual Studio.
4. Open the generated solution file, and build it.
