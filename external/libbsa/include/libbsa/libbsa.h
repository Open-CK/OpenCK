/*  libbsa

    A library for reading and writing BSA files.

    Copyright (C) 2012-2013    WrinklyNinja

    This file is part of libbsa.

    libbsa is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    libbsa is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libbsa.  If not, see
    <http://www.gnu.org/licenses/>.
*/

/**
    @file libbsa.h
    @brief This file contains the API frontend.

    @note libbsa is *not* thread safe. Thread safety is a goal, but one that
          has not yet been achieved. Bear this in mind if using it in a
          multi-threaded client.

    @section var_sec Variable Types

    libbsa uses character strings and integers for information input/output.
      - All strings are null-terminated byte character strings encoded in
        UTF-8.
      - All return codes and version and compression flags are unsigned
        integers at least 16 bits in size.
      - All array sizes are unsigned integers at least 16 bits in size.
      - File paths are case-sensitive if and only if the underlying file system
        is case-sensitive.
      - Paths to files inside BSAs are lowercase, use backslashes as directory
        separators, and are relative to the BSA's root directory, which is not
        specified. For example, `/meshes/shovel.nif` is incorrect:
        `meshes\shovel.nif` is correct. libbsa will automatically correct any
        incorrect paths to individual files, but will not correct incorrect
        regular expression paths.
      - Regular expressions use the
        [ECMAScript](http://www.cplusplus.com/reference/regex/ECMAScript/)
        syntax.

    @section memory_sec Memory Management

    libbsa manages the memory of strings and arrays it returns internally, so
    such strings and arrays should not be deallocated by the client.

    Data returned by a function lasts until a function is called which returns
    data of the same type (eg. a string is stored until the client calls
    another function which returns a string, an integer array lasts until
    another integer array is returned, etc.).

    All allocated memory is freed when bsa_close() is called, except the string
    returned by bsa_get_error_message(), which is allocated for the lifetime of
    the library.

    While the source path given in a bsa_asset object must be valid until the
    next call to bsa_save(), the memory allocated by the client for the path
    string may be freed at any point after the object's use.
*/

#ifndef __LIBBSA_H__
#define __LIBBSA_H__

#include <stddef.h>
#include <stdint.h>

#if defined(_MSC_VER)
//MSVC doesn't support C99, so do the stdbool.h definitions ourselves.
//START OF stdbool.h DEFINITIONS.
#       ifndef __cplusplus
#               define bool     _Bool
#               define true     1
#               define false   0
#       endif
#       define __bool_true_false_are_defined   1
//END OF stdbool.h DEFINITIONS.
#else
#       include <stdbool.h>
#endif

// set up dll import/export decorators
// when compiling the dll on windows, ensure LIBBSA_EXPORT is defined.  clients
// that use this header do not need to define anything to import the symbols
// properly.
#if defined(_WIN32) || defined(_WIN64)
#       ifdef LIBBSA_STATIC
#               define LIBBSA
#   elif defined LIBBSA_EXPORT
#       define LIBBSA __declspec(dllexport)
#   else
#       define LIBBSA __declspec(dllimport)
#   endif
#else
#   define LIBBSA
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*------------------------------
   Types
------------------------------*/

/**
    @brief A structure that holds all game-specific data used by libbsa.
    @details Holds an index of all the files inside a BSA file. Abstracts the
             definition of libbsa' internal state while still providing type
             safety across the library's functions. Multiple handles can also
             be made for each BSA file, though it should be kept in mind that
             libbsa is not thread-safe.
*/
    typedef struct _bsa_handle_int * bsa_handle;

    /*********************//**
        @name Return Codes
        @brief Error codes signify an issue that caused a function to exit
               prematurely. If a function exits prematurely, a reversal of any
               changes made during its execution is attempted before it exits.
    *************************/
    /**@{*/
    ///< The function completed successfully.
    LIBBSA extern const unsigned int LIBBSA_OK;
    LIBBSA extern const unsigned int LIBBSA_ERROR_INVALID_ARGS;  ///< Invalid arguments were given for the function.
    LIBBSA extern const unsigned int LIBBSA_ERROR_NO_MEM;  ///< The library was unable to allocate the required memory.
    LIBBSA extern const unsigned int LIBBSA_ERROR_FILESYSTEM_ERROR;  ///< There was an error encountered while performing a filesystem interaction (eg. reading, writing).
    LIBBSA extern const unsigned int LIBBSA_ERROR_BAD_STRING;  ///< A UTF-8 string contains characters that do not have Windows-1252 code points, or vice versa.
    LIBBSA extern const unsigned int LIBBSA_ERROR_ZLIB_ERROR;  ///< zlib reported an error during file compression or decompression.
    LIBBSA extern const unsigned int LIBBSA_ERROR_PARSE_FAIL;  ///< There was an error in parsing a BSA.

    /**
        @brief Matches the value of the highest-numbered return code.
        @details Provided in case clients wish to incorporate additional return
                 codes in their implementation and desire some method of
                 avoiding value conflicts.
    */
    LIBBSA extern const unsigned int LIBBSA_RETURN_MAX;
    /* No doubt there will be more... */

    /**@}*/
    /*********************//**
        @name BSA Version Flags
        @brief Used to specify the type of BSA to create. Only one should be
               specified at any one time.
    *************************/
    /**@{*/
    LIBBSA extern const unsigned int LIBBSA_VERSION_TES3;  ///< Specifies the BSA structure supported by TES III: Morrowind.
    LIBBSA extern const unsigned int LIBBSA_VERSION_TES4;  ///< Specifies the BSA structure supported by TES IV: Oblivion.
    LIBBSA extern const unsigned int LIBBSA_VERSION_TES5;  ///< Specifies the BSA structure supported by TES V:Skyrim, Fallout 3, Fallout: New Vegas.

    /**@}*/
    /*********************//**
        @name BSA Compression Flags
        @brief Used to specify the compression level to use for a BSA. Only one
               should be specified at any one time.
    *************************/
    /**@{*/
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_0;    ///< Use no compression.
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_1;  ///< Use the lowest level of compression.
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_2;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_3;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_4;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_5;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_6;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_7;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_8;
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_9;  ///< Use the highest level of compression.
    LIBBSA extern const unsigned int LIBBSA_COMPRESS_LEVEL_NOCHANGE;  ///< Use the same level of compression as was used in the opened BSA.

    /**@}*/

    /*********************//**
        @name Version Functions
    *************************/
    /**@{*/
    /**
        @brief Checks for library compatibility.
        @details Checks whether the loaded libbsa is compatible with the given
                 version of libbsa, abstracting library stability policy away
                 from clients. The version numbering used is major.minor.patch.
        @param versionMajor The major version number to check.
        @param versionMinor The minor version number to check.
        @param versionPatch The patch version number to check.
        @returns True if the library versions are compatible, false otherwise.
    */
    LIBBSA bool bsa_is_compatible(const unsigned int versionMajor,
                                  const unsigned int versionMinor,
                                  const unsigned int versionPatch);

    /**
        @brief Gets the library version.
        @details Outputs the major, minor and patch version numbers for the
                 loaded libbsa. The version numbering used is
                 major.minor.patch.
        @param versionMajor A pointer to the major version number.
        @param versionMinor A pointer to the minor version number.
        @param versionPatch A pointer to the patch version number.
    */
    LIBBSA unsigned int bsa_get_version(unsigned int * const versionMajor,
                                        unsigned int * const versionMinor,
                                        unsigned int * const versionPatch);

    /**@}*/

    /*********************************//**
        @name Error Handling Functions
    *************************************/
    /**@{*/
    /**
       @brief Returns the message for the last error or warning encountered.
       @details Outputs a string giving the a message containing the details of
                the last error or warning encountered by a function. Each time
                this function is called, the memory for the previous message is
                freed, so only one error message is available at any one time.
       @param details A pointer to the error details string outputted by the
                      function.
       @returns A return code.
    */
    LIBBSA unsigned int bsa_get_error_message(const char ** const details);

    /**@}*/

    /***************************************//**
        @name Lifecycle Management Functions
    *******************************************/
    /**@{*/
    /**
        @brief Initialise a new BSA handle.
        @details Opens a BSA file, outputting a handle that holds an index of
                 its contents. If the file doesn't exist then a handle for a
                 new file will be created. You can create multiple handles.
        @param bh A pointer to the handle that is created by the function.
        @param path A string containing the relative or absolute path to the
                    BSA file to be opened.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_open(bsa_handle * const bh,
                                 const char * const path);

    /**
        @brief Save a BSA at the given path. Not yet implemented.
        @details Opens a BSA file, outputting a handle that holds an index of
                 its contents. If the file doesn't exist then a handle for a
                 new file will be created. You can create multiple handles.
        @param bh The handle the function acts on.
        @param path A string containing the relative or absolute path to the
                    BSA file to be saved to.
        @param flags A version flag and a compression flag combined using the
                     bitwise OR operator.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_save(bsa_handle bh,
                                 const char * const path,
                                 const unsigned int flags);

    /**
        @brief Closes an existing handle.
        @details Closes an existing handle, freeing any memory allocated during
                 its use.
        @param bh The handle to be destroyed.
    */
    LIBBSA void bsa_close(bsa_handle bh);

    /**@}*/

    /***************************************//**
        @name Content Reading Functions
    *******************************************/
    /**@{*/
    /**
        @brief Selectively outputs asset paths in a BSA.
        @details Gets all the assets indexed in a handle with internal paths
                 that match the given regular expression.
        @param bh The handle the function acts on.
        @param assetRegex The regular expression to match asset paths against.
        @param assetPaths The outputted array of asset paths. If no matching
                          assets are found, this will be `NULL`.
        @param numAssets The size of the outputted array. If no matching assets
                         are found, this will be `0`.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_get_assets(bsa_handle bh,
                                       const char * const assetRegex,
                                       const char * const ** const assetPaths,
                                       size_t * const numAssets);

    /**
        @brief Checks if a specific asset is in a BSA.
        @param bh The handle the function acts on.
        @param assetPath The internal asset path to look for.
        @param result The result of the check: `true` if the asset was found,
                      `false` otherwise.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_contains_asset(bsa_handle bh,
                                           const char * const assetPath,
                                           bool * const result);

    /**@}*/

    /***************************************//**
        @name Content Extraction Functions
    *******************************************/
    /**@{*/
    /**
        @brief Selectively extracts assets from a BSA.
        @details Extracts all the assets with internal paths that match the
                 given regular expression to the given destination path,
                 maintaining the directory structure they had inside the BSA.
        @param bh The handle the function acts on.
        @param assetRegex The regular expression to match asset paths
                            against.
        @param destPath The folder path to which assets should be extracted.
        @param assetPaths An array of the internal paths of the assets
                          extracted. If no assets are extracted, this will be
                          `NULL`.
        @param numAssets The size of the outputted array.
        @param overwrite If an asset is to be extracted to a path that already
                         exists, this decides what will happen. If `true`, the
                         existing file will be overwritten, otherwise the asset
                         will not be extracted.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_extract_assets(bsa_handle bh,
                                           const char * const assetRegex,
                                           const char * const destPath,
                                           const char * const ** const assetPaths,
                                           size_t * const numAssets,
                                           const bool overwrite);

    /**
        @brief Extracts an asset from a BSA to the filesystem.
        @details Extracts the given asset to the given location. If a file
                 already exists at the destination path, this function will
                 return with an error code.
        @param bh The handle the function acts on.
        @param assetPath The path of the asset inside the BSA.
        @param destPath The file path to which the asset should be extracted.
        @param overwrite If the asset is to be extracted to a path that already
                         exists, this decides what will happen. If `true`, the
                         existing file will be overwritten, otherwise the asset
                         will not be extracted.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_extract_asset(bsa_handle bh,
                                          const char * const assetPath,
                                          const char * const destPath,
                                          const bool overwrite);

    /**
        @brief Extracts an asset from a BSA into memory.
        @details Extracts the given asset to the output array.
        @param bh The handle the function acts on.
        @param assetPath The path of the asset inside the BSA.
        @param data The output byte array containing the asset's data.
        @param size The size of the output byte array.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_extract_asset_to_memory(bsa_handle bh,
                                                    const char * const assetPath,
                                                    const uint8_t ** const data,
                                                    size_t * size);

    /**@}*/

    /***************************************//**
        @name Misc. Functions
    *******************************************/
    /**@{*/
    /**
        @brief Calculates the CRC32 of an asset.
        @details Calculates the 32-bit CRC of the given asset without
                 extracting it. The CRC parameters are those used by the
                 Boost.CRC library's `crc_32_type` type.
        @param bh The handle the function acts on.
        @param assetPath The internal asset path to calculate the CRC32 of.
        @param checksum The calculated checksum.
        @returns A return code.
    */
    LIBBSA unsigned int bsa_calc_checksum(bsa_handle bh,
                                          const char * const assetPath,
                                          uint32_t * const checksum);

    /**@}*/

#ifdef __cplusplus
}
#endif

#endif
