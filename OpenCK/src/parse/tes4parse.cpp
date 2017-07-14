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

// Declare field types as QVariants
Q_DECLARE_METATYPE(CNAMField*)
Q_DECLARE_METATYPE(INTVField*)

TES4Parse::TES4Parse () { }

/**
 * Parse TES4 record.
 * @brief TES4Parse::readTES4
 * @param in File stream.
 * @param TES4 Object to store parsed information.
 */
void TES4Parse::readTES4(QDataStream* in, TES4Record* TES4)
{
    ushort dataCount = 0;  // Count to reference bytes read

    QByteArray typeBuffer("");
    typeBuffer.resize(4);

    QString typeChar(ReadBytes::readCharArray(in, &typeBuffer));
    QChar* type = typeChar.data();
    TES4->setType(type);

    QByteArray buffer;

    TES4->setDataSize(ReadBytes::readUInt32_t(in, &buffer));
    TES4->setFlags(ReadBytes::readUInt32_t(in, &buffer));
    TES4->setId(ReadBytes::readUInt32_t(in, &buffer));
    TES4->setRevision(ReadBytes::readUInt32_t(in, &buffer));
    TES4->setVersion(ReadBytes::readUInt16_t(in, &buffer));
    TES4->setUnknown(ReadBytes::readUInt16_t(in, &buffer));

    readHEDR(in, TES4, &dataCount);

    // Read next field whilst there is still space in the record
    while (dataCount < TES4->getDataSize()) {
        buffer.clear();
        buffer.resize(4);
        QString type(ReadBytes::readCharArray(in, &buffer));
        QChar* nextField = type.data();

        if (QString::compare(QString(nextField), "CNAM") == 0) {
            readCNAM(in, TES4, nextField, &dataCount);
        } else if (QString::compare(QString(nextField), "INTV") == 0) {
            readINTV(in, TES4, nextField, &dataCount);
        }

        // TODO: Populate with remaining subrecord reading methods
    }
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
    void TES4Parse::readHEDR(QDataStream* in, TES4Record* TES4, ushort* dataCount)
{       
    QByteArray typeBuffer("");
    typeBuffer.resize(4);

    QString typeChar(ReadBytes::readCharArray(in, &typeBuffer));
    QChar* type = typeChar.data();

    QByteArray buffer;

    uint16_t dataSize = ReadBytes::readUInt16_t(in, &buffer);

    char* temp = ReadBytes::readCharArray(in, &buffer);
    QDataStream stream(buffer);
    float version = ReadBytes::readFloat(in, &stream);

    int32_t numRecords = ReadBytes::readInt32_t(in, &buffer);
    uint32_t nextObjectId = ReadBytes::readUInt32_t(in, &buffer);

    HEDRField* HEDR = new HEDRField(type, dataSize, version, numRecords, nextObjectId);
    TES4->setHEDR(HEDR);
    *(dataCount) += 18;
}
#pragma warning(pop)

/**
 * Parse CNAM subrecord
 * @brief TES4Parse::readCNAM
 * @param in QDataStream from file.
 * @param TES4 TES4 Record.
 * @param type 4-byte type code.
 * @param dataCount Loop control variable.
 */
void TES4Parse::readCNAM(QDataStream* in, TES4Record* TES4, QChar *type, ushort* dataCount)
{
    QByteArray buffer;
    buffer.clear();

    uint16_t dataSize = ReadBytes::readUInt16_t(in, &buffer);
    QString author = ReadBytes::readString(in, &buffer);

    CNAMField* CNAM = new CNAMField(type, dataSize, &author);
    TES4->setCNAM(CNAM);
    *(dataCount) += dataSize + 6;
}

/**
 * Parse INTV subrecord
 * @brief TES4Parse::readINTV
 * @param in QDataStream from file.
 * @param TES4 TES4 Record.
 * @param type 4-byte type code.
 * @param dataCount Loop control variable.
 */
void TES4Parse::readINTV(QDataStream* in, TES4Record* TES4, QChar* type, ushort* dataCount)
{
    QByteArray buffer;
    buffer.clear();

    uint16_t dataSize = ReadBytes::readUInt16_t(in, &buffer);
    uint32_t internalVersion = ReadBytes::readUInt32_t(in, &buffer);

    INTVField* INTV = new INTVField(type, dataSize, internalVersion);
    TES4->setINTV(INTV);
    *(dataCount) += dataSize + 6;
}

