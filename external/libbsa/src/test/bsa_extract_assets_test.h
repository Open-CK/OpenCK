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

#ifndef LIBBSA_TEST_BSA_EXTRACT_ASSETS_H
#define LIBBSA_TEST_BSA_EXTRACT_ASSETS_H

#include "bsa_handle_operation_test.h"

#include <boost/algorithm/string.hpp>

namespace libbsa {
    namespace test {
        class bsa_extract_assets : public BsaHandleOperationTest {
        protected:
            bsa_extract_assets() :
                assetPaths(nullptr),
                numAssets(0) {}

            ~bsa_extract_assets() {
                boost::filesystem::remove_all(outputPath);
            }

            const char * const * assetPaths;
            size_t numAssets;
        };

        TEST_F(bsa_extract_assets, shouldFailIfUnininitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldFailIfNullAssetRegexIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_assets(handle, NULL, outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldFailIfNullDestPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_assets(handle, assetRegex.c_str(), NULL, &assetPaths, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldFailIfNullAssetPathsIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), NULL, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldFailIfNullNumAssetsPointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, NULL, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldOutputANullArrayPointerAndZeroSizeIfNoAssetsMatchTheAssetRegex) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, noMatchAssetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldCreateTheOutputPathIfItDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
            ASSERT_FALSE(boost::filesystem::exists(outputPath));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_TRUE(boost::filesystem::exists(outputPath));
        }

        TEST_F(bsa_extract_assets, shouldSucceedIfTheOutputPathExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
            boost::filesystem::create_directories(outputPath);

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
        }

        TEST_F(bsa_extract_assets, shouldFailIfOverwriteIsFalseAndDestPathAlreadyExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            boost::filesystem::create_directories(outputPath);
            boost::filesystem::ofstream out(outputPath / assetPath);
            out << "test";
            out.close();

            EXPECT_EQ(LIBBSA_ERROR_FILESYSTEM_ERROR, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_extract_assets, shouldSucceedIfOverwriteIsTrueAndDestPathAlreadyExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            boost::filesystem::ofstream out(outputPath / assetPath);
            out << "test";
            out.close();

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, true));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));

            ASSERT_EQ(1, numAssets);
            EXPECT_EQ(boost::to_lower_copy(assetPath), assetPaths[0]);
        }

        TEST_F(bsa_extract_assets, shouldSucceedIfOverwriteIsTrueAndDestPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, true));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));

            ASSERT_EQ(1, numAssets);
            EXPECT_EQ(boost::to_lower_copy(assetPath), assetPaths[0]);
        }

        TEST_F(bsa_extract_assets, shouldSucceedIfOverwriteIsFalseAndDestPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_assets(handle, assetRegex.c_str(), outputPath.string().c_str(), &assetPaths, &numAssets, false));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));

            ASSERT_EQ(1, numAssets);
            EXPECT_EQ(boost::to_lower_copy(assetPath), assetPaths[0]);
        }
    }
}

#endif
