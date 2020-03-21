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

#include "genericbsa.h"
#include "error.h"
#include "libbsa/libbsa.h"

#include <boost/algorithm/string.hpp>
#include <boost/crc.hpp>
#include <boost/filesystem.hpp>
#include <boost/locale.hpp>

namespace fs = boost::filesystem;

using namespace std;

namespace libbsa {
    GenericBsa::GenericBsa(const boost::filesystem::path& path) : filePath(path) {}

    bool GenericBsa::HasAsset(const std::string& assetPath) const {
        std::string normalisedAssetPath = NormaliseAssetPath(assetPath);

        return std::any_of(begin(assets), end(assets), [&](const BsaAsset& asset) {
            return asset.path == normalisedAssetPath;
        });
    }

    BsaAsset GenericBsa::GetAsset(const std::string& assetPath) const {
        std::string normalisedAssetPath = NormaliseAssetPath(assetPath);

        auto it = find_if(begin(assets), end(assets), [&](const BsaAsset& asset) {
            return asset.path == normalisedAssetPath;
        });

        if (it != end(assets))
            return *it;

        return BsaAsset();
    }

    std::vector<BsaAsset> GenericBsa::GetMatchingAssets(const regex& regex) const {
        vector<BsaAsset> matchingAssets;
        copy_if(begin(assets), end(assets), back_inserter(matchingAssets), [&](const BsaAsset& asset) {
            return regex_match(asset.path, regex);
        });

        return matchingAssets;
    }

    void GenericBsa::Extract(const std::string& assetPath,
                             const uint8_t ** const _data,
                             size_t * const _size) const {
        //Get asset data.
        BsaAsset data = GetAsset(assetPath);
        if (data.path.empty())
            throw error(LIBBSA_ERROR_INVALID_ARGS, "Asset not found");

        pair<uint8_t*, size_t> dataPair;
        try {
            //Read file data.
            boost::filesystem::ifstream in(filePath, ios::binary);
            in.exceptions(ios::failbit | ios::badbit | ios::eofbit);  //Causes ifstream::failure to be thrown if problem is encountered.

            dataPair = ReadData(in, data);

            *_data = dataPair.first;
            *_size = dataPair.second;

            in.close();
        }
        catch (ios_base::failure& e) {
            delete[] dataPair.first;
            throw error(LIBBSA_ERROR_FILESYSTEM_ERROR, e.what());
        }
    }

    void GenericBsa::Extract(const std::string& assetPath,
                             const boost::filesystem::path& destRootPath,
                             const bool overwrite) const {
        fs::path outFilePath = destRootPath / assetPath;

        if (!overwrite && fs::exists(outFilePath))
            throw error(LIBBSA_ERROR_FILESYSTEM_ERROR, "The file \"" + outFilePath.string() + "\" already exists.");

        try {
            //Create parent directories.
            fs::create_directories(outFilePath.parent_path());  //This creates any directories in the path that don't already exist.

            const uint8_t * data;
            size_t dataSize;
            Extract(assetPath, &data, &dataSize);

            //Write new file.
            boost::filesystem::ofstream out(outFilePath, ios::binary | ios::trunc);
            out.exceptions(ios::failbit | ios::badbit | ios::eofbit);  //Causes ifstream::failure to be thrown if problem is encountered.

            out.write((char*)data, dataSize);

            out.close();
        }
        catch (ios_base::failure& e) {
            throw error(LIBBSA_ERROR_FILESYSTEM_ERROR, e.what());
        }
    }

    void GenericBsa::Extract(const vector<BsaAsset>& assetsToExtract,
                             const boost::filesystem::path& destRootPath,
                             const bool overwrite) const {
        for (const auto& asset : assetsToExtract) {
            Extract(asset.path, destRootPath, overwrite);
        }
    }

    uint32_t GenericBsa::CalcChecksum(const std::string& assetPath) const {
        const uint8_t * data;
        size_t dataSize;
        Extract(assetPath, &data, &dataSize);

        //Calculate the checksum now.
        boost::crc_32_type result;
        result.process_bytes(data, dataSize);

        return result.checksum();
    }

    std::string GenericBsa::ToUTF8(const std::string& str) {
        try {
            return boost::locale::conv::to_utf<char>(str, "Windows-1252", boost::locale::conv::stop);
        }
        catch (boost::locale::conv::conversion_error& e) {
            throw error(LIBBSA_ERROR_BAD_STRING, "\"" + str + "\" cannot be encoded in Windows-1252.");
        }
    }

    std::string GenericBsa::FromUTF8(const std::string& str) {
        try {
            return boost::locale::conv::from_utf<char>(str, "Windows-1252", boost::locale::conv::stop);
        }
        catch (boost::locale::conv::conversion_error& e) {
            throw error(LIBBSA_ERROR_BAD_STRING, "\"" + str + "\" cannot be encoded in Windows-1252.");
        }
    }

    std::string GenericBsa::NormaliseAssetPath(const std::string& assetPath) {
        std::string out(boost::to_lower_copy(assetPath));

        boost::replace_all(out, "/", "\\");

        if (out[0] == '\\')
            out = out.substr(1);

        return out;
    }
}
