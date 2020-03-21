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

#ifndef __LIBBSA_TES3STRUCTS_H__
#define __LIBBSA_TES3STRUCTS_H__

#include "genericbsa.h"
#include <stdint.h>
#include <string>

#include <boost/filesystem.hpp>

/* File format infos:
    <http://www.uesp.net/wiki/Tes3Mod:BSA_File_Format>

    This header file defines the constants, structures and functions specific
    to the Tes3-type BSA, which is used by Morrowind.
*/

namespace libbsa {
    namespace tes3 {
        class BSA : public GenericBsa {
        public:
            static const uint32_t VERSION = 0x100;

            BSA(const boost::filesystem::path& path);
            void Save(const boost::filesystem::path& path,
                      const uint32_t version,
                      const uint32_t compression);

            //Check if a given file is a Tes3-type BSA.
            static bool IsBSA(const boost::filesystem::path& path);
        private:
            std::pair<uint8_t*, size_t> ReadData(std::ifstream& in,
                                                 const BsaAsset& data) const;

            static uint64_t CalcHash(const std::string& assetPath);

            uint32_t hashOffset;

            static bool hash_comp(const BsaAsset& first, const BsaAsset& second);
            static bool path_comp(const BsaAsset& first, const BsaAsset& second);

            struct Header {
                uint32_t version;
                uint32_t hashOffset;
                uint32_t fileCount;
            };

            struct FileRecord {
                uint32_t size;
                uint32_t offset;
            };
        };
    }
}

#endif
