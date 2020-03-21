# Settings passed on the command line:
#
# PROJECT_LIBS_DIR = the directory which all external libraries may be referenced from.
# PROJECT_ARCH = the build architecture
# PROJECT_LINK = whether to build a static or dynamic library.

##############################
# General Settings
##############################

cmake_minimum_required (VERSION 2.8)
project (libbsa)
include(ExternalProject)

option(BUILD_SHARED_LIBS "Build a shared library" ON)
option(PROJECT_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)

ExternalProject_Add(zlib
                    PREFIX "external"
                    URL "https://zlib.net/zlib-1.2.11.tar.gz"
                    INSTALL_COMMAND "")
ExternalProject_Get_Property(zlib SOURCE_DIR BINARY_DIR)
set (ZLIB_INCLUDE_DIRS ${SOURCE_DIR} ${BINARY_DIR})
IF (MSVC)
    set (ZLIB_LIBRARIES optimized "${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}zlibstatic${CMAKE_STATIC_LIBRARY_SUFFIX}"
                    debug "${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}zlibstaticd${CMAKE_STATIC_LIBRARY_SUFFIX}")
ELSE ()
    set (ZLIB_LIBRARIES "${BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}z${CMAKE_STATIC_LIBRARY_SUFFIX}")
ENDIF ()

ExternalProject_Add(GTest
                    PREFIX "external"
                    URL "https://github.com/google/googletest/archive/release-1.7.0.tar.gz"
                    INSTALL_COMMAND "")
ExternalProject_Get_Property(GTest SOURCE_DIR BINARY_DIR)
set (GTEST_INCLUDE_DIRS "${SOURCE_DIR}/include")
set (GTEST_LIBRARIES "${BINARY_DIR}/${CMAKE_CFG_INTDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")

ExternalProject_Add(testing-plugins
                    PREFIX "external"
                    URL "https://github.com/WrinklyNinja/testing-plugins/archive/1.1.0.tar.gz"
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND ""
                    INSTALL_COMMAND "")

set (Boost_USE_STATIC_LIBS ${PROJECT_STATIC_RUNTIME})
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME ${PROJECT_STATIC_RUNTIME})

find_package(Boost REQUIRED COMPONENTS iostreams filesystem system locale)

set (PROJECT_SRC "${CMAKE_SOURCE_DIR}/src/api/_bsa_handle_int.cpp"
                 "${CMAKE_SOURCE_DIR}/src/api/genericbsa.cpp"
                 "${CMAKE_SOURCE_DIR}/src/api/libbsa.cpp"
                 "${CMAKE_SOURCE_DIR}/src/api/tes3bsa.cpp"
                 "${CMAKE_SOURCE_DIR}/src/api/tes4bsa.cpp")

set (PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/libbsa/libbsa.h"
                     "${CMAKE_SOURCE_DIR}/src/api/_bsa_handle_int.h"
                     "${CMAKE_SOURCE_DIR}/src/api/bsa_asset.h"
                     "${CMAKE_SOURCE_DIR}/src/api/error.h"
                     "${CMAKE_SOURCE_DIR}/src/api/genericbsa.h"
                     "${CMAKE_SOURCE_DIR}/src/api/tes3bsa.h"
                     "${CMAKE_SOURCE_DIR}/src/api/tes4bsa.h")

set (TEST_SRC "${CMAKE_SOURCE_DIR}/src/test/main.cpp")

set (TEST_HEADERS "${CMAKE_SOURCE_DIR}/src/test/bsa_calc_checksum_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_contains_asset_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_extract_asset_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_extract_asset_to_memory_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_extract_assets_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_get_assets_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_handle_operation_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_open_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/bsa_save_test.h"
                  "${CMAKE_SOURCE_DIR}/src/test/libbsa_test.h")

source_group("Header Files" FILES ${PROJECT_HEADERS} ${TEST_HEADERS})

include_directories("${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/include"
                    ${Boost_INCLUDE_DIRS}
                    ${GTEST_INCLUDE_DIRS}
                    ${ZLIB_INCLUDE_DIRS})

##############################
# Platform-Specific Settings
##############################

# Settings when compiling and cross-compiling on Linux.
IF (CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -std=c++11 -fPIC")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -fPIC")
    IF (PROJECT_STATIC_RUNTIME)
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
        set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
        set (CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
    ENDIF ()

    set(PROJECT_LIBRARIES "pthread")
ENDIF ()

# Settings when compiling with MSVC.
IF (MSVC)
    # Update compiler flags.
    IF (PROJECT_STATIC_RUNTIME)
        FOREACH(flag
            CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
            CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
            STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
            SET("${flag}" "${${flag}} /EHsc ")
        ENDFOREACH()
    ENDIF ()

    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:MSVCRTD")
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:MSVCRTD")
ENDIF ()

##############################
# Targets
##############################

# Build libbsa library.
add_library           (bsa ${PROJECT_SRC} ${PROJECT_HEADERS})
add_dependencies      (bsa zlib)
target_link_libraries (bsa ${Boost_LIBRARIES} ${ZLIB_LIBRARIES})

# Build libbsa tester.
add_executable        (tests ${TEST_SRC} ${TEST_HEADERS})
add_dependencies      (tests GTest testing-plugins)
target_link_libraries (tests bsa ${GTEST_LIBRARIES} ${PROJECT_LIBRARIES})


##############################
# Set Target-Specific Flags
##############################

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    IF (BUILD_SHARED_LIBS)
        set_target_properties (bsa PROPERTIES COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} LIBBSA_EXPORT")
    ELSE ()
        set_target_properties (bsa PROPERTIES COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} LIBBSA_STATIC")
        set_target_properties (tests PROPERTIES COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} LIBBSA_STATIC")
    ENDIF ()
ENDIF ()


##############################
# Post-Build Steps
##############################

# Copy testing plugins
ExternalProject_Get_Property(testing-plugins SOURCE_DIR)
add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SOURCE_DIR}
        $<TARGET_FILE_DIR:tests>)

find_package(Doxygen)
find_package(LATEX)

IF (DOXYGEN_FOUND AND LATEX_FOUND)
    # Run Doxygen and LaTeX to generate readme
    add_custom_command(TARGET bsa POST_BUILD
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
        COMMAND "${CMAKE_SOURCE_DIR}/docs/latex/make.bat"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/docs")
ENDIF ()
