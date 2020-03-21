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

#ifndef LIBBSA_TEST_BSA_GET_ASSETS_H
#define LIBBSA_TEST_BSA_GET_ASSETS_H

#include "bsa_handle_operation_test.h"

#include <boost/algorithm/string.hpp>

namespace libbsa {
    namespace test {
        class bsa_get_assets : public BsaHandleOperationTest {
        protected:
            bsa_get_assets() :
                assetPaths(nullptr),
                numAssets(0) {}

            const char * const * assetPaths;
            size_t numAssets;
        };

        TEST_F(bsa_get_assets, shouldFailIfUnininitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_get_assets(handle, assetRegex.c_str(), &assetPaths, &numAssets));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_get_assets, shouldFailIfNullAssetRegexIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_get_assets(handle, NULL, &assetPaths, &numAssets));
        }

        TEST_F(bsa_get_assets, shouldFailIfNullAssetPathsIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_get_assets(handle, assetRegex.c_str(), NULL, &numAssets));
        }

        TEST_F(bsa_get_assets, shouldFailIfNullNumAssetsPointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_get_assets(handle, assetRegex.c_str(), &assetPaths, NULL));
        }

        TEST_F(bsa_get_assets, shouldOutputANullArrayPointerAndZeroSizeIfNoAssetsMatchTheAssetRegex) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_get_assets(handle, noMatchAssetRegex.c_str(), &assetPaths, &numAssets));

            EXPECT_EQ(NULL, assetPaths);
            EXPECT_EQ(0, numAssets);
        }

        TEST_F(bsa_get_assets, shouldOutputMatchingPathsCorrectly) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_get_assets(handle, assetRegex.c_str(), &assetPaths, &numAssets));

            ASSERT_EQ(1, numAssets);
            EXPECT_EQ(boost::to_lower_copy(assetPath), assetPaths[0]);
        }
    }
}

#endif
