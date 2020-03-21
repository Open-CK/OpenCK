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

#ifndef LIBBSA_TEST_BSA_EXTRACT_ASSET_H
#define LIBBSA_TEST_BSA_EXTRACT_ASSET_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_extract_asset : public BsaHandleOperationTest {
        protected:
            ~bsa_extract_asset() {
                boost::filesystem::remove_all(outputPath);
            }
        };

        TEST_F(bsa_extract_asset, shouldFailIfUnininitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), false));
        }

        TEST_F(bsa_extract_asset, shouldFailIfNullAssetPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset(handle, NULL, outputPath.string().c_str(), false));
        }

        TEST_F(bsa_extract_asset, shouldFailIfAssetPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset(handle, invalidPath.string().c_str(), outputPath.string().c_str(), false));
        }

        TEST_F(bsa_extract_asset, shouldFailIfNullDestPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset(handle, assetPath.c_str(), NULL, false));
        }

        TEST_F(bsa_extract_asset, shouldCreateOutputPathIfItDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
            ASSERT_FALSE(boost::filesystem::exists(outputPath));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), false));

            EXPECT_TRUE(boost::filesystem::exists(outputPath));
        }

        TEST_F(bsa_extract_asset, shouldFailIfOverwriteIsFalseAndDestPathAlreadyExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            boost::filesystem::create_directories(outputPath);
            boost::filesystem::ofstream out(outputPath / assetPath);
            out << "test";
            out.close();

            EXPECT_EQ(LIBBSA_ERROR_FILESYSTEM_ERROR, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), false));
        }

        TEST_F(bsa_extract_asset, shouldSucceedIfOverwriteIsTrueAndDestPathAlreadyExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            boost::filesystem::ofstream out(outputPath / assetPath);
            out << "test";
            out.close();

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), true));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));
        }

        TEST_F(bsa_extract_asset, shouldSucceedIfOverwriteIsTrueAndDestPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
            ASSERT_FALSE(boost::filesystem::exists(outputPath / assetPath));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), true));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));
        }

        TEST_F(bsa_extract_asset, shouldSucceedIfOverwriteIsFalseAndDestPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
            ASSERT_FALSE(boost::filesystem::exists(outputPath / assetPath));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_asset(handle, assetPath.c_str(), outputPath.string().c_str(), false));

            EXPECT_TRUE(boost::filesystem::exists(outputPath / assetPath));
            EXPECT_EQ(assetChecksum, getChecksum(outputPath / assetPath));
        }
    }
}

#endif
