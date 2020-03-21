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

#ifdef __GNUC__  // Workaround for GCC linking error.
#pragma message("GCC detected: Defining BOOST_NO_CXX11_SCOPED_ENUMS to avoid linking errors for boost::filesystem::copy_file().")
#define BOOST_NO_CXX11_SCOPED_ENUMS
#endif

#include "bsa_calc_checksum_test.h"
#include "bsa_contains_asset_test.h"
#include "bsa_extract_asset_test.h"
#include "bsa_extract_asset_to_memory_test.h"
#include "bsa_extract_assets_test.h"
#include "bsa_get_assets_test.h"
#include "bsa_open_test.h"
#include "bsa_save_test.h"
#include "libbsa_test.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
