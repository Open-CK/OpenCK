/*  libbsa

    A library for reading and writing BSA files.

    Copyright (C) 2016 Oliver Hamlet

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

#ifndef LIBBSA_BSA_HANDLE_OPERATION_TEST_H
#define LIBBSA_BSA_HANDLE_OPERATION_TEST_H

#include "libbsa/libbsa.h"

#include <boost/crc.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <gtest/gtest.h>

namespace libbsa {
    namespace test {
        class BsaHandleOperationTest : public ::testing::Test {
        protected:
            BsaHandleOperationTest() :
                handle(nullptr),
                invalidPath("./missing"),
                nonBsaPath("./Skyrim/Data/Blank.esp"),
                tes4BsaPath("./Oblivion/Data/Blank.bsa"),
                tes5BsaPath("./Skyrim/Data/Blank.bsa"),
                assetPath("license"),
                assetChecksum(0x0F168B66),
                assetRegex("L.+"),
                invalidAssetRegex("L("),
                noMatchAssetRegex(".+\\.dds"),
                outputPath("./out") {}

            ~BsaHandleOperationTest() {
                bsa_close(handle);
            }

            bsa_handle handle;
            const boost::filesystem::path invalidPath;
            const boost::filesystem::path nonBsaPath;
            const boost::filesystem::path tes4BsaPath;
            const boost::filesystem::path tes5BsaPath;
            const boost::filesystem::path outputPath;

            const std::string assetPath;
            const std::string assetRegex;
            const std::string invalidAssetRegex;
            const std::string noMatchAssetRegex;

            const uint32_t assetChecksum;

            static uint32_t getChecksum(boost::filesystem::path path) {
                boost::crc_32_type result;
                boost::filesystem::ifstream in(path, std::ios::binary);

                do {
                    constexpr size_t bufferSize = 8192;
                    char buffer[bufferSize];

                    in.read(buffer, bufferSize);
                    result.process_bytes(buffer, in.gcount());
                } while (in);

                return result.checksum();
            }
        };
    }
}

#endif
