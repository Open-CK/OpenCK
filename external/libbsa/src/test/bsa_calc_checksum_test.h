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

#ifndef LIBBSA_TEST_BSA_CALC_CHECKSUM_H
#define LIBBSA_TEST_BSA_CALC_CHECKSUM_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_calc_checksum : public BsaHandleOperationTest {
        protected:
            uint32_t checksum;
        };

        TEST_F(bsa_calc_checksum, shouldFailIfUninitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_calc_checksum(handle, assetPath.c_str(), &checksum));
        }

        TEST_F(bsa_calc_checksum, shouldFailIfNullAssetPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_calc_checksum(handle, NULL, &checksum));
        }

        TEST_F(bsa_calc_checksum, shouldFailIfAssetPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_calc_checksum(handle, invalidPath.string().c_str(), &checksum));
        }

        TEST_F(bsa_calc_checksum, shouldFailIfNullChecksumPointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_calc_checksum(handle, assetPath.c_str(), NULL));
        }

        TEST_F(bsa_calc_checksum, shouldOutputChecksumCorrectly) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_calc_checksum(handle, assetPath.c_str(), &checksum));

            EXPECT_EQ(assetChecksum, checksum);
        }
    }
}

#endif
