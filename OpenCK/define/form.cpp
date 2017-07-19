/*
** form.cpp
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

#include "form.h"

//!@file form.cpp Source for parsing Forms from .esm and .esp files.

/**
 * Constructs the Form object with the default values of 0.
 * @brief Constructs the Form with default values of 0.
 */
Form::Form()
{
    header.type = 0;
    header.dataSize = 0;
    header.flags = 0;
    header.id = 0;
    header.revision = 0;
    header.version = 0;
    header.unknown = 0;
}

/**
 * Destroys Form object.
 * @brief Destroys Form object.
 */
Form::~Form() { }

/**
 * Reads subrecord header values from a QDataStream.
 * @brief Reads a subrecord header.
 * @param in QDataStream to read from
 * @param read Integer representing the amount of bytes read.
 * @return Subrecord header.
 */
SubrecordHeader Form::readSubrecord(QDataStream* in, quint32* read)
{
    QByteArray buffer;
    SubrecordHeader header;
    quint32 type = ReadFile::readUInt32_t(in, &buffer);
    header.type = qToBigEndian(type);
    header.size = ReadFile::readUInt16_t(in, &buffer);
    *(read) += 6;

    if (header.type == 'XXXX') {
        header.size = ReadFile::readUInt32_t(in, &buffer);
        header.type = ReadFile::readUInt32_t(in, &buffer);
        ReadFile::readUInt16_t(in, &buffer);
        *(read) += 10;
    }

    return header;
}
