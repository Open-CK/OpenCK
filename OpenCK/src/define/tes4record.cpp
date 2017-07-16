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

#include "tes4record.h"

/************************************/
/* TES4 Record functions            */
/************************************/

/**
 * Initialise record object with appropriate Name.
 * @brief TES4Record::TES4Record
 */
TES4Record::TES4Record()
{
    RecordName name = RecordName::Header;
    setName(name);
}

TES4Record::~TES4Record() { }

/**
 * Set the name enum of the record.
 * @brief TES4Record::setName
 * @param inName Enum value to set.
 */
void TES4Record::setName(RecordName inName)
{
    name = inName;
}

/**
 * Add a HEDR subrecord to TES4 record.
 * @brief TES4Record::setHEDR
 * @param inHEDR Subrecord to add.
 */
void TES4Record::setHEDR(TES4HEDR* inHEDR)
{
    HEDR = inHEDR;
}

/**
 * Add a CNAM subrecord to TES4 record.
 * @brief TES4Record::setCNAM
 * @param inCNAM Subrecord to add.
 */
void TES4Record::setCNAM(TES4CNAM* inCNAM)
{
    CNAM = inCNAM;
}

/**
 * Add an INTV subrecord to TES4 record.
 * @brief TES4Record::setINTV
 * @param inINTV Subrecord to add.
 */
void TES4Record::setINTV(TES4INTV* inINTV)
{
    INTV = inINTV;
}

/**
 * Retrieve the name enum of the record.
 * @brief TES4Record::getName
 * @return Name enum.
 */
RecordName TES4Record::getName()
{
    return name;
}

/**
 * Retrieve the HEDR subrecord.
 * @brief TES4Record::getHEDR
 * @return HEDR subrecord.
 */
TES4HEDR* TES4Record::getHEDR()
{
    return HEDR;
}

/**
 * Retrieve the CNAM subrecord.
 * @brief TES4Record::getCNAM
 * @return CNAM subrecord.
 */
TES4CNAM* TES4Record::getCNAM()
{
    return CNAM;
}

/**
 * Retrieve the INTV subrecord.
 * @brief TES4Record::getINTV
 * @return INTV subrecord.
 */
TES4INTV* TES4Record::getINTV()
{
    return INTV;
}

/************************************/
/* HEDR Subrecord functions         */
/************************************/

/**
 * Initialise a new HEDR subrecord with appropriate values.
 * @brief TES4HEDR::TES4HEDR
 * @param inType 4-character type code.
 * @param inDataSize Number of bytes of data.
 * @param inVersion Unknown version float.
 * @param inNumRecords Number of records in master/plugin file.
 * @param inNextObjectId ID of the next appearing object.
 */
TES4HEDR::TES4HEDR(QChar *inType, uint16_t inDataSize, float inVersion,
                     int32_t inNumRecords, uint32_t inNextObjectId)
{
    setType(inType);
    setDataSize(inDataSize);
    version = inVersion;
    numRecords = inNumRecords;
    nextObjectId = inNextObjectId;

    FieldName inName = FieldName::Header_Data;
    setName(inName);
}

TES4HEDR::~TES4HEDR() { }

/**
 * Set the name enumerator of the subrecord.
 * @brief TES4HEDR::setName
 * @param inName Name enumerator.
 */
void TES4HEDR::setName(FieldName inName)
{
    name = inName;
}

/**
 * Set the version float of the HEDR subrecord.
 * @brief TES4HEDR::setVersion
 * @param inVersion Unknown version float.
 */
void TES4HEDR::setVersion(float inVersion)
{
    version = inVersion;
}

/**
 * Set the number of records in the master/plugin file.
 * @brief TES4HEDR::setNumRecords
 * @param inNumRecords Number of records.
 */
void TES4HEDR::setNumRecords(int32_t inNumRecords)
{
    numRecords = inNumRecords;
}

/**
 * Set the ID of the next appearing object.
 * @brief TES4HEDR::setNextObjectId
 * @param inNextObjectId Next Object ID.
 */
void TES4HEDR::setNextObjectId(uint32_t inNextObjectId)
{
    nextObjectId = inNextObjectId;
}

/**
 * Retrieve the name enum of the subrecord.
 * @brief TES4HEDR::getName
 * @return Name enumerator.
 */
FieldName TES4HEDR::getName()
{
    return name;
}

/**
 * Retrieve the version float of the subrecord.
 * @brief TES4HEDR::getVersion
 * @return Unknown version float.
 */
float TES4HEDR::getVersion()
{
    return version;
}

/**
 * Retrieve the number of records in the master/plugin file.
 * @brief TES4HEDR::getNumRecords
 * @return Number of records.
 */
int32_t TES4HEDR::getNumRecords()
{
    return numRecords;
}

/**
 * Return the ID of the next appearing object.
 * @brief TES4HEDR::getNextObjectId
 * @return Next Object ID.
 */
uint32_t TES4HEDR::getNextObjectId()
{
    return nextObjectId;
}

/************************************/
/* CNAM Subrecord functions         */
/************************************/

/**
 * Initialise a CNAM subrecord with appropriate values.
 * @brief TES4CNAM::TES4CNAM
 * @param inType 4-character type code.
 * @param inDataSize Size of the data in bytes.
 * @param inAuthor Author of the master/plugin file.
 */
TES4CNAM::TES4CNAM(QChar* inType, uint16_t inDataSize, QString inAuthor)
{
    setType(inType);
    setDataSize(inDataSize);
    author = inAuthor;

    FieldName inName = FieldName::Author_Information;
    setName(inName);
}

TES4CNAM::~TES4CNAM() { }

/**
 * Set the name enumerator of the subrecord.
 * @brief TES4CNAM::setName
 * @param inName Name enum.
 */
void TES4CNAM::setName(FieldName inName)
{
    name = inName;
}

/**
 * Set the master/plugin file author.
 * @brief TES4CNAM::setAuthor
 * @param inAuthor Author string.
 */
void TES4CNAM::setAuthor(QString inAuthor)
{
    author = inAuthor;
}

/**
 * Retrieve the subrecord Name enumerator.
 * @brief TES4CNAM::getName
 * @return Name enum.
 */
FieldName TES4CNAM::getName()
{
    return name;
}

/**
 * Retrieve the master/plugin file author.
 * @brief TES4CNAM::getAuthor
 * @return Author string.
 */
QString TES4CNAM::getAuthor()
{
    return author;
}

/************************************/
/* INTV Subrecord functions         */
/************************************/

/**
 * Initialise an INTV subrecord with appropriate values.
 * @brief TES4INTV::TES4INTV
 * @param inType 4-character type code.
 * @param inDataSize Size of data in bytes.
 * @param inVersion Unknown integer (internal version?)
 */
TES4INTV::TES4INTV(QChar* inType, uint16_t inDataSize, uint32_t inVersion)
{
    setType(inType);
    setDataSize(inDataSize);
    internalVersion = inVersion;

    FieldName inName = FieldName::Internal_Version;
    setName(inName);
}

TES4INTV::~TES4INTV() { }

/**
 * Set the Name enumerator of the subrecord.
 * @brief TES4INTV::setName
 * @param inName Name enum.
 */
void TES4INTV::setName(FieldName inName)
{
    name = inName;
}

/**
 * Set internal version (?) value.
 * @brief TES4INTV::setInternalVersion
 * @param inVersion Internal version.
 */
void TES4INTV::setInternalVersion(uint32_t inVersion)
{
    internalVersion = inVersion;
}

/**
 * Retrieve the Name enumerator of the subrecord.
 * @brief TES4INTV::getName
 * @return Name enum.
 */
FieldName TES4INTV::getName()
{
    return name;
}

/**
 * Retrieve the internal version (?)
 * @brief TES4INTV::getInternalVersion
 * @return Unknown integer (internal version?)
 */
uint32_t TES4INTV::getInternalVersion()
{
    return internalVersion;
}
