/*
** tes4parse.cpp
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
** Created Date: 12-Jul-2017
*/

#include "tes4parse.h"

TES4Parse::TES4Parse () { }

/**
 * Parse TES4 record.
 * @brief TES4Parse::readTES4
 * @param in File stream.
 * @param TES4 Object to store parsed information.
 */
void TES4Parse::readTES4(QDataStream* in, TES4Record* TES4)
{
    // ushort dataCount = 0;  Count to reference bytes read, currently unused while the while loop is commented out.

    QByteArray typeBuffer("");
    typeBuffer.resize(4);

    char typeArray[4];
    char* typeChar = ReadBytes::readCharArray(in, &typeBuffer);
    strcpy(typeArray, typeChar);
    memcpy(TES4->entries.type, typeArray, 4);

    QByteArray buffer;

    TES4->entries.dataSize = ReadBytes::readUInt32_t(in, &buffer);
    TES4->entries.flags = ReadBytes::readUInt32_t(in, &buffer);
    TES4->entries.id = ReadBytes::readUInt32_t(in, &buffer);
    TES4->entries.revision = ReadBytes::readUInt32_t(in, &buffer);
    TES4->entries.version = ReadBytes::readUInt16_t(in, &buffer);
    TES4->entries.unknown = ReadBytes::readUInt16_t(in, &buffer);

    readHEDR(in, TES4);

    // Read next field whilst there is still space in the record
   // while (dataCount < TES4->entries.dataSize) {
        char* nextField = ReadBytes::readCharArray(in, &buffer);

        if (QString::compare(nextField, "CNAM") == 0) {
            readCNAM(in, TES4, nextField);
        }
        // TODO: Populate with subrecord reading methods
    //}
}

/**
 * Parse the HEDR subrecord.
 * @brief TES4Parse::readHEDR
 * @param in File stream.
 * @param TES4 Object to store record information.
 */
#pragma warning(push)
#pragma warning(disable: 4189)
//disable warning regarding a buffer we use to populate a byte array that is not used otherwise.
void TES4Parse::readHEDR(QDataStream* in, TES4Record* TES4)
{
    QByteArray typeBuffer("");
    typeBuffer.resize(4);

    char fieldTypeArray[4];
    char* fieldType = ReadBytes::readCharArray(in, &typeBuffer);
    strcpy(fieldTypeArray, fieldType);
    memcpy(TES4->HEDR.type, fieldTypeArray, 4);

    QByteArray buffer;

    TES4->HEDR.dataSize = ReadBytes::readUInt16_t(in, &buffer);

    char* temp = ReadBytes::readCharArray(in, &buffer);
    QDataStream stream(buffer);
    TES4->HEDR.entries.version = ReadBytes::readFloat(in, &stream);

    TES4->HEDR.entries.numRecords = ReadBytes::readInt32_t(in, &buffer);
    TES4->HEDR.entries.nextObjectId = ReadBytes::readUInt32_t(in, &buffer);

    qDebug() << "HEDR Entries are:" << TES4->HEDR.entries.version << TES4->HEDR.entries.numRecords << TES4->HEDR.entries.nextObjectId;
}
#pragma warning(pop)

void TES4Parse::readCNAM(QDataStream* in, TES4Record* TES4, char* type)
{
    CNAMField* CNAM = new CNAMField;

    QByteArray buffer;
    buffer.clear();

    char fieldTypeArray[4];
    strcpy(fieldTypeArray, type);
    memcpy(CNAM->type, fieldTypeArray, 4);


    uint16_t dataSize = ReadBytes::readUInt16_t(in, &buffer);
    CNAM->dataSize = dataSize;

    qDebug() << "CNAM dataSize is" << CNAM->dataSize;
}
