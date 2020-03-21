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

#ifndef LIBBSA_TEST_BSA_SAVE_H
#define LIBBSA_TEST_BSA_SAVE_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_save : public BsaHandleOperationTest {
        protected:
            bsa_save() :
                tempBsaPath("./temp.bsa"),
                newBsaPath("./new.bsa") {}

            ~bsa_save() {
                boost::filesystem::remove(newBsaPath);
            }

            const boost::filesystem::path tempBsaPath;
            const boost::filesystem::path newBsaPath;
        };

        TEST_F(bsa_save, shouldFailIfUnininitialisedHandleIsGiven) {
            unsigned int ret = ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_9);
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ret);
        }

        TEST_F(bsa_save, shouldFailIfNullPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, NULL, LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_9));
        }

        TEST_F(bsa_save, shouldFailIfNoVersionFlagIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_COMPRESS_LEVEL_9));
        }

        TEST_F(bsa_save, shouldFailIfMoreThanOneVersionFlagIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES3 | LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_0));
        }

        TEST_F(bsa_save, shouldFailIfNoCompressionFlagIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES4));
        }

        TEST_F(bsa_save, shouldFailIfMoreThanOneCompressionFlagIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_1 | LIBBSA_COMPRESS_LEVEL_9));
        }

        TEST_F(bsa_save, shouldFailIfTheBsaHandledNoLongerExists) {
            boost::filesystem::copy_file(tes4BsaPath.string(), tempBsaPath);

            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tempBsaPath.string().c_str()));

            boost::filesystem::remove(tempBsaPath);

            EXPECT_EQ(LIBBSA_ERROR_FILESYSTEM_ERROR, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_9));
        }

        TEST_F(bsa_save, shouldFailIfThePathGivenAlreadyExists) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_save(handle, tes4BsaPath.string().c_str(), LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_9));
        }

        TEST_F(bsa_save, shouldWriteOutBsaToGivenPathIfArgumentsAreValid) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_save(handle, newBsaPath.string().c_str(), LIBBSA_VERSION_TES4 | LIBBSA_COMPRESS_LEVEL_NOCHANGE));

            EXPECT_TRUE(boost::filesystem::exists(newBsaPath));
            EXPECT_EQ(getChecksum(tes4BsaPath), getChecksum(newBsaPath));
        }
    }
}

#endif
