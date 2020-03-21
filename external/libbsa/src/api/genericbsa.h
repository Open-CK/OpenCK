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

#ifndef __LIBBSA_GENERICBSA_H__
#define __LIBBSA_GENERICBSA_H__

#include "bsa_asset.h"
#include <stdint.h>
#include <string>
#include <list>
#include <regex>

#include <boost/filesystem/fstream.hpp>

namespace libbsa {
    // Class for generic BSA data manipulation functions.
    struct GenericBsa {
    public:
        GenericBsa(const boost::filesystem::path& path);

        virtual void Save(const boost::filesystem::path& path,
                          const uint32_t version,
                          const uint32_t compression) = 0;

        bool HasAsset(const std::string& assetPath) const;
        BsaAsset GetAsset(const std::string& assetPath) const;
        std::vector<BsaAsset> GetMatchingAssets(const std::regex& regex) const;

        void Extract(const std::string& assetPath,
                     const uint8_t ** const data,
                     size_t * const size) const;

        void Extract(const std::string& assetPath,
                     const boost::filesystem::path& destRootPath,
                     const bool overwrite) const;

        void Extract(const std::vector<BsaAsset>& assetsToExtract,
                     const boost::filesystem::path& destRootPath,
                     const bool overwrite) const;

        uint32_t CalcChecksum(const std::string& assetPath) const;
    protected:
        // Reads the asset data into memory, at .first, with size .second.
        // Remember to free the memory once used.
        virtual std::pair<uint8_t*, size_t> ReadData(std::ifstream& in,
                                                     const BsaAsset& data) const = 0;

        const boost::filesystem::path filePath;
        std::list<BsaAsset> assets;

        // Only ever need to convert between Windows-1252 and UTF-8.
        static std::string ToUTF8(const std::string& str);
        static std::string FromUTF8(const std::string& str);

        // Replaces all forwardslashes with backslashes, and lowercases letters.
        static std::string NormaliseAssetPath(const std::string& assetPath);
    };
}

#endif
