/*
** recordparent.cpp
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

/**
 * Constructs the Form object with the default values of 0.
 * @brief Constructs the Form with default values of 0.
 */
Form::Form()
{
    char type[] = "NUL";
    strcpy(header.type, type);
    header.dataSize = 0;
    header.flags = 0;
    header.id = 0;
    header.revision = 0;
    header.version = 0;
    header.unknown = 0;
}

/**
 * Destroys Form object.
 * @brief Form::~Form Destroys Form object.
 */
Form::~Form() { }

/**
 * Sets the Type member by converting a character pointer to an array.
 * @brief Form::setType Sets the Type member of a record.
 * @param array Pointer at start of array.
 */
void Form::setType(char *array)
{
    for (uint8_t i = 0; i < 4; i++) {
        header.type[i] = *(array);
        array++;
    }
}

/**
 * Sets the Type member of a SubrecordHeader by converting a character pointer to an array.
 * @brief Form::setSubType Sets the Type member of a SubrecordHeader.
 * @param array Pointer at start of array.
 * @param header SubrecordHeader to assign type to.
 */
void Form::setSubType(char *array, SubrecordHeader *header)
{
    for (uint8_t i = 0; i < 4; i++) {
        header->type[i] = *(array);
        array++;
    }
}

/**
 * Reads subrecord header values from a QDataStream.
 * @brief Form::readSubrecord Reads a subrecord header.
 * @param in QDataStream to read from.
 * @return Subrecord header.
 */
SubrecordHeader Form::readSubrecord(QDataStream *in)
{
    QByteArray typeBuffer;
    QByteArray buffer;
    SubrecordHeader header;
    setSubType(ReadFile::readChar(in, &typeBuffer), &header);
    header.size = ReadFile::readUInt16_t(in, &buffer);

    return header;
}
