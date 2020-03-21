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

#ifndef LIBBSA_BSA_HANDLE_INT_H
#define LIBBSA_BSA_HANDLE_INT_H

#include "bsa_asset.h"
#include "genericbsa.h"
#include <string>

//Class for generic BSA data manipulation functions.
struct _bsa_handle_int {
public:
    _bsa_handle_int(const boost::filesystem::path& path);
    ~_bsa_handle_int();

    libbsa::GenericBsa * getBsa() const;
    char ** getExtAssets() const;
    size_t getExtAssetsNum() const;

    void setExtAssets(const std::vector<libbsa::BsaAsset>& assets);
    void freeExtAssets();
private:
    libbsa::GenericBsa * bsa;

    //External data array pointers and sizes.
    char ** extAssets;
    size_t extAssetsNum;

    // std::string to null-terminated uint8_t string converter.
    static char * ToNewCString(const std::string& str);
};

#endif
