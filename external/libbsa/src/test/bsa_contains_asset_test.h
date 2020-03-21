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

#ifndef LIBBSA_TEST_BSA_CONTAINS_ASSET_H
#define LIBBSA_TEST_BSA_CONTAINS_ASSET_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_contains_asset : public BsaHandleOperationTest {
        protected:
            bool result;
        };

        TEST_F(bsa_contains_asset, shouldFailIfUnininitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_contains_asset(handle, assetPath.c_str(), &result));
        }

        TEST_F(bsa_contains_asset, shouldFailIfNullAssetPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_contains_asset(handle, NULL, &result));
        }

        TEST_F(bsa_contains_asset, shouldFailIfNullResultPointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_contains_asset(handle, assetPath.c_str(), NULL));
        }

        TEST_F(bsa_contains_asset, shouldOutputFalseIfAssetPathIsNotFound) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_contains_asset(handle, invalidPath.string().c_str(), &result));

            EXPECT_FALSE(result);
        }

        TEST_F(bsa_contains_asset, shouldOutputTrueIfAssetPathIsFound) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_contains_asset(handle, assetPath.c_str(), &result));

            EXPECT_TRUE(result);
        }
    }
}

#endif
