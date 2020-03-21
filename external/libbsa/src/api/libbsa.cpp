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

#include "libbsa/libbsa.h"
#include "_bsa_handle_int.h"
#include "genericbsa.h"
#include "tes3bsa.h"
#include "tes4bsa.h"
#include "error.h"

#include <bitset>
#include <codecvt>
#include <boost/filesystem.hpp>
#include <locale>
#include <regex>
#include <unordered_set>

using namespace std;
using namespace libbsa;

/*------------------------------
   Global variables
------------------------------*/

const unsigned int LIBBSA_VERSION_MAJOR = 2;
const unsigned int LIBBSA_VERSION_MINOR = 0;
const unsigned int LIBBSA_VERSION_PATCH = 0;

thread_local std::string extErrorString;

/*------------------------------
   Constants
------------------------------*/

// Return codes
const unsigned int LIBBSA_OK = 0;
const unsigned int LIBBSA_ERROR_INVALID_ARGS = 1;
const unsigned int LIBBSA_ERROR_NO_MEM = 2;
const unsigned int LIBBSA_ERROR_FILESYSTEM_ERROR = 3;
const unsigned int LIBBSA_ERROR_BAD_STRING = 4;
const unsigned int LIBBSA_ERROR_ZLIB_ERROR = 5;
const unsigned int LIBBSA_ERROR_PARSE_FAIL = 6;
const unsigned int LIBBSA_RETURN_MAX = LIBBSA_ERROR_PARSE_FAIL;

/* BSA save flags */
/* Use only one version flag. */
const unsigned int LIBBSA_VERSION_TES3 = 0x00000001;
const unsigned int LIBBSA_VERSION_TES4 = 0x00000002;
const unsigned int LIBBSA_VERSION_TES5 = 0x00000004;
/* Use only one compression flag. */
const unsigned int LIBBSA_COMPRESS_LEVEL_0 = 0x00000010;
const unsigned int LIBBSA_COMPRESS_LEVEL_1 = 0x00000020;
const unsigned int LIBBSA_COMPRESS_LEVEL_2 = 0x00000040;
const unsigned int LIBBSA_COMPRESS_LEVEL_3 = 0x00000080;
const unsigned int LIBBSA_COMPRESS_LEVEL_4 = 0x00000100;
const unsigned int LIBBSA_COMPRESS_LEVEL_5 = 0x00000200;
const unsigned int LIBBSA_COMPRESS_LEVEL_6 = 0x00000400;
const unsigned int LIBBSA_COMPRESS_LEVEL_7 = 0x00000800;
const unsigned int LIBBSA_COMPRESS_LEVEL_8 = 0x00001000;
const unsigned int LIBBSA_COMPRESS_LEVEL_9 = 0x00002000;
const unsigned int LIBBSA_COMPRESS_LEVEL_NOCHANGE = 0x00004000;

unsigned int c_error(const unsigned int code, const char * what) {
    extErrorString = what;
    return code;
}

/*------------------------------
   Version Functions
------------------------------*/

/* Returns whether this version of libbsa is compatible with the given
   version of libbsa. */
LIBBSA bool bsa_is_compatible(const unsigned int versionMajor,
                              const unsigned int versionMinor,
                              const unsigned int versionPatch) {
    return versionMajor == LIBBSA_VERSION_MAJOR;
}

LIBBSA unsigned int bsa_get_version(unsigned int * const versionMajor,
                                    unsigned int * const versionMinor,
                                    unsigned int * const versionPatch) {
    if (versionMajor == nullptr || versionMinor == nullptr || versionPatch == nullptr)
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    *versionMajor = LIBBSA_VERSION_MAJOR;
    *versionMinor = LIBBSA_VERSION_MINOR;
    *versionPatch = LIBBSA_VERSION_PATCH;

    return LIBBSA_OK;
}

/*------------------------------
   Error Handling Functions
------------------------------*/

/* Outputs a string giving the a message containing the details of the
   last error or warning encountered by a function called for the given
   game handle. */
LIBBSA unsigned int bsa_get_error_message(const char ** const details) {
    if (details == NULL)
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    if (extErrorString.empty())
        *details = nullptr;
    else
        *details = extErrorString.c_str();

    return LIBBSA_OK;
}

/*----------------------------------
   Lifecycle Management Functions
----------------------------------*/

/* Opens a BSA file at path, returning a handle.  */
LIBBSA unsigned int bsa_open(bsa_handle * const bh, const char * const path) {
    if (bh == NULL || path == NULL)  //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    //Set the locale to get encoding conversions working correctly.
    std::locale::global(std::locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>));
    boost::filesystem::path::imbue(std::locale());

    if (!boost::filesystem::exists(path))
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Given path does not exist.");

    //Create handle for the appropriate BSA type.
    try {
        *bh = new _bsa_handle_int(path);
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }
    catch (ios_base::failure& e) {
        return c_error(LIBBSA_ERROR_FILESYSTEM_ERROR, e.what());
    }

    return LIBBSA_OK;
}

/* Create a BSA at the specified path. The 'flags' argument consists of a set
   of bitwise OR'd constants defining the version of the BSA and the
   compression level used (and whether the compression is forced). */
LIBBSA unsigned int bsa_save(bsa_handle bh,
                             const char * const path,
                             const unsigned int flags) {
    if (bh == NULL || path == NULL)  //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    //First we need to see what flags are set.
    if (flags & LIBBSA_VERSION_TES3 && !(flags & LIBBSA_COMPRESS_LEVEL_0))
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Morrowind BSAs cannot be compressed.");

    //Check that the version flag is valid.
    std::bitset<3> version(flags & (LIBBSA_VERSION_TES3 | LIBBSA_VERSION_TES4 | LIBBSA_VERSION_TES5));
    if (version.none())
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Must specify one version.");
    if (version.count() > 1)
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Cannot specify more than one version.");

    //Now remove version flag from flags and check for compression flag duplication.
    std::bitset<16> compression(flags ^ version.to_ulong());
    if (compression.none())
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Must specify one compression level.");
    if (compression.count() > 1)
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Cannot specify more than one compression level.");

    try {
        bh->getBsa()->Save(path, version.to_ulong(), compression.to_ulong());
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }
    catch (ios_base::failure& e) {
        return c_error(LIBBSA_ERROR_FILESYSTEM_ERROR, e.what());
    }

    return LIBBSA_OK;
}

/* Closes the BSA associated with the given handle, freeing any memory
   allocated during its use. */
LIBBSA void bsa_close(bsa_handle bh) {
    delete bh;
}

/*------------------------------
   Content Reading Functions
------------------------------*/

LIBBSA unsigned int bsa_get_assets(bsa_handle bh,
                                   const char * const assetRegex,
                                   const char * const ** const assetPaths,
                                   size_t * const numAssets) {
    if (bh == NULL || assetRegex == NULL || assetPaths == NULL || numAssets == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    // Free memory if in use.
    bh->freeExtAssets();

    //Init values.
    *assetPaths = NULL;
    *numAssets = 0;

    try {
        // Build regex expression.
        regex regex = std::regex(assetRegex, regex::extended | regex::icase);

        //We don't know how many matches there will be, so put all matches into a temporary buffer first.
        vector<BsaAsset> temp = bh->getBsa()->GetMatchingAssets(regex);

        if (temp.empty())
            return LIBBSA_OK;

        //Fill external array.
        bh->setExtAssets(temp);
    }
    catch (regex_error& e) {
        return c_error(LIBBSA_ERROR_INVALID_ARGS, e.what());
    }
    catch (bad_alloc& e) {
        return c_error(LIBBSA_ERROR_NO_MEM, e.what());
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }

    *assetPaths = bh->getExtAssets();
    *numAssets = bh->getExtAssetsNum();

    return LIBBSA_OK;
}

/* Checks if a specific asset, found within the BSA at assetPath, is in the given BSA. */
LIBBSA unsigned int bsa_contains_asset(bsa_handle bh,
                                       const char * const assetPath,
                                       bool * const result) {
    if (bh == NULL || assetPath == NULL || result == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    *result = bh->getBsa()->HasAsset(assetPath);

    return LIBBSA_OK;
}

/*--------------------------------
   Content Extraction Functions
--------------------------------*/

LIBBSA unsigned int bsa_extract_assets(bsa_handle bh,
                                       const char * const assetRegex,
                                       const char * const destPath,
                                       const char * const ** const assetPaths,
                                       size_t * const numAssets,
                                       const bool overwrite) {
    if (bh == NULL || assetRegex == NULL || destPath == NULL || assetPaths == NULL || numAssets == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    //Free memory if in use.
    bh->freeExtAssets();

    //Init values.
    *assetPaths = NULL;
    *numAssets = 0;

    try {
        //Build regex expression.
        regex regex = std::regex(string(reinterpret_cast<const char*>(assetRegex)), regex::extended | regex::icase);

        //We don't know how many matches there will be, so put all matches into a temporary buffer first.
        vector<BsaAsset> temp = bh->getBsa()->GetMatchingAssets(regex);

        if (temp.empty())
            return LIBBSA_OK;

        bh->getBsa()->Extract(temp, string(reinterpret_cast<const char*>(destPath)), overwrite);

        bh->setExtAssets(temp);
    }
    catch (regex_error& e) {
        return c_error(LIBBSA_ERROR_INVALID_ARGS, e.what());
    }
    catch (bad_alloc& e) {
        return c_error(LIBBSA_ERROR_NO_MEM, e.what());
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }

    *assetPaths = bh->getExtAssets();
    *numAssets = bh->getExtAssetsNum();

    return LIBBSA_OK;
}

/* Extracts a specific asset, found at assetPath, from a given BSA, to destPath. */
LIBBSA unsigned int bsa_extract_asset(bsa_handle bh,
                                      const char * const assetPath,
                                      const char * const destPath,
                                      const bool overwrite) {
    if (bh == NULL || assetPath == NULL || destPath == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    try {
        bh->getBsa()->Extract(assetPath, string(reinterpret_cast<const char*>(destPath)), overwrite);
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }

    return LIBBSA_OK;
}

/* Extracts a specific asset, found at assetPath, from a given BSA, to memory. */
LIBBSA unsigned int bsa_extract_asset_to_memory(bsa_handle bh,
                                                const char * const assetPath,
                                                const uint8_t ** const _data,
                                                size_t * _size) {
    if (bh == NULL || assetPath == NULL || _data == NULL || _size == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    try {
        bh->getBsa()->Extract(assetPath, _data, _size);
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }

    return LIBBSA_OK;
}

/*--------------------------------
   Misc. Functions
--------------------------------*/

LIBBSA unsigned int bsa_calc_checksum(bsa_handle bh,
                                      const char * const assetPath,
                                      uint32_t * const checksum) {
    if (bh == NULL || assetPath == NULL || checksum == NULL) //Check for valid args.
        return c_error(LIBBSA_ERROR_INVALID_ARGS, "Null pointer passed.");

    try {
        *checksum = bh->getBsa()->CalcChecksum(assetPath);
    }
    catch (error& e) {
        return c_error(e.code(), e.what());
    }

    return LIBBSA_OK;
}
