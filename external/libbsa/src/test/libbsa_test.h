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

#ifndef LIBBSA_TEST_H
#define LIBBSA_TEST_H

#include "libbsa/libbsa.h"

#include <thread>

#include <gtest/gtest.h>

namespace libbsa {
    namespace test {
        TEST(bsa_get_version, shouldFailIfPassedNullMajorVersionParameter) {
            unsigned int vMinor = 0;
            unsigned int vPatch = 0;
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_version(NULL, &vMinor, &vPatch));
        }

        TEST(bsa_get_version, shouldFailIfPassedNullMinorVersionParameter) {
            unsigned int vMajor = 0;
            unsigned int vPatch = 0;
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_version(&vMajor, NULL, &vPatch));
        }

        TEST(bsa_get_version, shouldFailIfPassedNullPatchVersionParameter) {
            unsigned int vMajor = 0;
            unsigned int vMinor = 0;
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_version(&vMajor, &vMinor, NULL));
        }

        TEST(bsa_get_version, shouldSucceedIfPassedNonNullParameters) {
            unsigned int vMajor = 0, vMinor = 0, vPatch = 0;
            EXPECT_EQ(LIBBSA_OK, bsa_get_version(&vMajor, &vMinor, &vPatch));
        }

        TEST(bsa_is_compatible, shouldReturnTrueIfMajorVersionIsEqual) {
            unsigned int vMajor = 0, vMinor = 0, vPatch = 0;
            ASSERT_EQ(LIBBSA_OK, bsa_get_version(&vMajor, &vMinor, &vPatch));

            EXPECT_TRUE(bsa_is_compatible(vMajor, vMinor + 1, vPatch + 1));
        }

        TEST(bsa_is_compatible, shouldReturnFalseIfMajorVersionIsNotEqual) {
            unsigned int vMajor = 0, vMinor = 0, vPatch = 0;
            ASSERT_EQ(LIBBSA_OK, bsa_get_version(&vMajor, &vMinor, &vPatch));

            EXPECT_FALSE(bsa_is_compatible(vMajor + 1, vMinor, vPatch));
        }

        TEST(bsa_get_error_message, shouldFailIfPassedNullPointer) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_error_message(NULL));
        }

        TEST(bsa_get_error_message, shouldOutputCorrectErrorMessageIfErrorHasOccurred) {
            ASSERT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_error_message(NULL));

            const char * error = nullptr;
            EXPECT_EQ(LIBBSA_OK, bsa_get_error_message(&error));
            EXPECT_STREQ("Null pointer passed.", error);
        }

        TEST(bsa_get_error_message, shouldOutputLastErrorMessageIfSuccessHasOccurredSinceLastError) {
            const char * error = nullptr;
            const char * lastError = nullptr;

            ASSERT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_error_message(NULL));
            ASSERT_EQ(LIBBSA_OK, bsa_get_error_message(&error));
            ASSERT_NE(nullptr, error);
            lastError = error;

            EXPECT_EQ(LIBBSA_OK, bsa_get_error_message(&error));
            ASSERT_EQ(lastError, error);
        }

        TEST(bsa_get_error_message, errorMessagesShouldBeLocalToTheThreadTheErrorWasCausedIn) {
            ASSERT_EQ(LIBBSA_ERROR_INVALID_ARGS, bsa_get_error_message(NULL));

            const char * error = nullptr;
            EXPECT_EQ(LIBBSA_OK, bsa_get_error_message(&error));
            EXPECT_STREQ("Null pointer passed.", error);

            std::thread otherThread([]() {
                const char * error = nullptr;
                EXPECT_EQ(LIBBSA_OK, bsa_get_error_message(&error));
                EXPECT_EQ(nullptr, error);
            });
            otherThread.join();
        }

        TEST(bsa_close, shouldNotThrowIfPassedANullPointer) {
            ASSERT_NO_THROW(bsa_close(NULL));
        }
    }
}

#endif
