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

#ifndef LIBBSA_TEST_BSA_EXTRACT_ASSET_TO_MEMORY_H
#define LIBBSA_TEST_BSA_EXTRACT_ASSET_TO_MEMORY_H

#include "bsa_handle_operation_test.h"

namespace libbsa {
    namespace test {
        class bsa_extract_asset_to_memory : public BsaHandleOperationTest {
        protected:
            const uint8_t * data;
            size_t size;

            inline static uint32_t getCrc(const uint8_t * const data, const size_t size) {
                boost::crc_32_type result;
                result.process_bytes(data, size);

                return result.checksum();
            }
        };

        TEST_F(bsa_extract_asset_to_memory, shouldFailIfUnininitialisedHandleIsGiven) {
            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset_to_memory(handle, assetPath.c_str(), &data, &size));
        }

        TEST_F(bsa_extract_asset_to_memory, shouldFailIfNullAssetPathIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset_to_memory(handle, NULL, &data, &size));
        }

        TEST_F(bsa_extract_asset_to_memory, shouldFailIfAssetPathDoesNotExist) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset_to_memory(handle, invalidPath.string().c_str(), &data, &size));
        }

        TEST_F(bsa_extract_asset_to_memory, shouldFailIfNullDataPointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset_to_memory(handle, assetPath.c_str(), NULL, &size));
        }

        TEST_F(bsa_extract_asset_to_memory, shouldFailIfNullSizePointerIsGiven) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_ERROR_INVALID_ARGS, ::bsa_extract_asset_to_memory(handle, assetPath.c_str(), &data, NULL));
        }

        TEST_F(bsa_extract_asset_to_memory, shouldOutputAssetBinaryDataToDataArrayCorrectly) {
            ASSERT_EQ(LIBBSA_OK, ::bsa_open(&handle, tes4BsaPath.string().c_str()));

            EXPECT_EQ(LIBBSA_OK, ::bsa_extract_asset_to_memory(handle, assetPath.c_str(), &data, &size));

            ASSERT_NE(nullptr, data);
            ASSERT_NE(0, size);
            EXPECT_EQ(assetChecksum, getCrc(data, size));
        }
    }
}

#endif
