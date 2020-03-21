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

#ifndef LIBBSA_BSA_ASSET_H
#define LIBBSA_BSA_ASSET_H

#include <cstdint>
#include <string>

namespace libbsa {
    // Class for generic BSA data.
    // Files that have not yet been written have 0 hash, size and offset.
    struct BsaAsset {
        inline BsaAsset() : hash(0), size(0), offset(0) {}

        // Asset data obtained from BSA.
        std::string path;
        uint64_t hash;

        uint32_t size;

        // This offset is from the beginning of the file - Tes3 BSAs use from
        // the beginning of the data section, so will have to adjust them.
        // Files that have not yet been written to the BSA have a 0 offset.
        uint32_t offset;
    };
}

#endif
