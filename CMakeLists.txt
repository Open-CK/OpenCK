cmake_minimum_required(VERSION 3.10)
project(OpenCK)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)

if(BUILD_DOC AND DOXYGEN_FOUND)

	doxygen_add_docs(doxygen_docs
					 doc
					 src
					 COMMENT "Generate documentation"
					 )

else()
	message("Doxygen required to build documentation.")
endif()

# Option macro
macro(set_option var default type docstring)
	if(NOT DEFINED %{var})
		set(${var} ${default})
	endif()
	set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Option for manually finding QT library path.
set_option(QT_DIR "" PATH "Path to QT library.")
if(QT_DIR)
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_DIR})
endif()

# cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find dependencies.
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Svg)

# Grab version from src/VERSION
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/VERSION")
	file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/src/VERSION" OPENCK_VERSION)
endif()

if(OPENCK_VERSION)
	add_definitions(-DOPENCK_VERSION="${OPENCK_VERSION}")
else()
	add_definitions(-DOPENCK_VERSION="0")
endif()

# Grab GIT revision and place in OPENCK_REVISION
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

if(GIT_SHA1)
add_definitions(-DOPENCK_REVISION="${GIT_SHA1}")
endif()


# Source files
include_directories(src)
add_subdirectory(src)