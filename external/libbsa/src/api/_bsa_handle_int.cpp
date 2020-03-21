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

#include "_bsa_handle_int.h"
#include "tes3bsa.h"
#include "tes4bsa.h"

#include <boost/algorithm/string.hpp>

using namespace libbsa;

_bsa_handle_int::_bsa_handle_int(const boost::filesystem::path& path) :
    extAssets(NULL),
    extAssetsNum(0) {
    if (tes3::BSA::IsBSA(path))
        bsa = new tes3::BSA(path);
    else
        bsa = new tes4::BSA(path);
}

_bsa_handle_int::~_bsa_handle_int() {
    for (size_t i = 0; i < extAssetsNum; i++)
        delete[] extAssets[i];
    delete[] extAssets;
}

GenericBsa * _bsa_handle_int::getBsa() const {
    return bsa;
}

char ** _bsa_handle_int::getExtAssets() const {
    return extAssets;
}

size_t _bsa_handle_int::getExtAssetsNum() const {
    return extAssetsNum;
}

void _bsa_handle_int::setExtAssets(const std::vector<BsaAsset>& assets) {
    extAssetsNum = assets.size();
    extAssets = new char*[extAssetsNum];

    size_t i = 0;
    for (const auto& asset : assets) {
        extAssets[i] = ToNewCString(asset.path);
        i++;
    }
}

void _bsa_handle_int::freeExtAssets() {
    if (extAssets != NULL) {
        for (size_t i = 0; i < extAssetsNum; i++)
            delete[] extAssets[i];
        delete[] extAssets;
        extAssets = NULL;
        extAssetsNum = 0;
    }
}

// std::string to null-terminated char string converter.
char * _bsa_handle_int::ToNewCString(const std::string& str) {
    char * p = new char[str.length() + 1];
    return strcpy(p, str.c_str());
}
