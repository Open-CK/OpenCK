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

#ifndef LIBBSA_TEST_BSA_OPEN_H
#define LIBBSA_TEST_BSA_OPEN_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_open : public BsaHandleOperationTest {};

        TEST_F(bsa_open, shouldFailIfNullHandlePointerIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_open(NULL, tes4BsaPath.string().c_str()));
        }

        TEST_F(bsa_open, shouldFailIfNullPathIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_open(&handle, NULL));
        }

        TEST_F(bsa_open, shouldFailIfNonExistentPathIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_open(&handle, invalidPath.string().c_str()));
        }

        TEST_F(bsa_open, shouldFailIfNonBsaPathIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_PARSE_FAIL, ::bsa_open(&handle, nonBsaPath.string().c_str()));
        }

        TEST_F(bsa_open, shouldSucceedIfValidPathToTes4BsaIsGiven) {
            EXPECT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));
        }

        TEST_F(bsa_open, shouldSucceedIfValidPathToTes5BsaIsGiven) {
            EXPECT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes5BsaPath.string().c_str()));
        }
    }
}

#endif
