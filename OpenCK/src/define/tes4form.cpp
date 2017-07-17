/*
** tes4record.cpp
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 10-Jul-2017
*/

#include "tes4form.h"

/**
 * Initialise header with the correct name enum (Header).
 * @brief Initialise header with correct name.
 */
TES4Form::TES4Form()
{
    name = FormName::Header;
}

/**
 * Destructs header object in memory.
 * @brief Destructs header object.
 */
TES4Form::~TES4Form() { }

/**
 * Loads the TES4 header from the data stream.
 * @brief Loads the header.
 * @param in The data stream to load the file from.
 */
void TES4Form::load(QDataStream* in)
{
    QByteArray buffer;

    Quint32 type = ReadFile::readUInt32_t(in, &buffer);
    header.type = qToBigEndian(type);
    header.dataSize = ReadFile::readUInt32_t(in, &buffer);
    header.flags = ReadFile::readUInt32_t(in, &buffer);
    header.id = ReadFile::readUInt32_t(in, &buffer);
    header.revision = ReadFile::readUInt32_t(in, &buffer);
    header.version = ReadFile::readUInt16_t(in, &buffer);
    header.unknown = ReadFile::readUInt16_t(in, &buffer);

    int read = 0;

    while (read < header.dataSize) {
        SubrecordHeader sHeader = readSubrecord(in);

        switch (sHeader.type) {
            case 'HEDR':
                version = ReadFile::readFloat(in, &buffer);
                records = ReadFile::readUInt32_t(in, &buffer);
                nextID = ReadFile::readUInt32_t(in, &buffer);
                read += 18;
                break;
            case 'CNAM':
                author = ReadFile::readString(in, &buffer);
                read += (6 + author.length() + 1);
                break;
            case 'SNAM':
                desc = ReadFile::readString(in, &buffer);
                read += (6 + desc.length() + 1);
                break;
            case 'INTV':
                intv = ReadFile::readUInt32_t(in, &buffer);
                read += 10;
                break;
            case 'INCC':
                incc = ReadFile::readUInt32_t(in, &buffer);
                read += 10;
                break;
        }

    }
}
