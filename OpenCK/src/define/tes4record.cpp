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

//Initialise object with empty data
TES4Record::TES4Record()
{
    RecordName name = RecordName::Header;
    setName(name);
}

TES4Record::~TES4Record() { }

void TES4Record::setName(RecordName inName)
{
    name = inName;
}

void TES4Record::setHEDR(TES4HEDR* inHEDR)
{
    HEDR = inHEDR;
}

void TES4Record::setCNAM(TES4CNAM* inCNAM)
{
    CNAM = inCNAM;
}

void TES4Record::setINTV(TES4INTV* inINTV)
{
    INTV = inINTV;
}

RecordName TES4Record::getName()
{
    return name;
}

TES4HEDR* TES4Record::getHEDR()
{
    return HEDR;
}

TES4CNAM* TES4Record::getCNAM()
{
    return CNAM;
}

TES4INTV* TES4Record::getINTV()
{
    return INTV;
}

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

void TES4HEDR::setName(FieldName inName)
{
    name = inName;
}

void TES4HEDR::setVersion(float inVersion)
{
    version = inVersion;
}

void TES4HEDR::setNumRecords(int32_t inNumRecords)
{
    numRecords = inNumRecords;
}

void TES4HEDR::setNextObjectId(uint32_t inNextObjectId)
{
    nextObjectId = inNextObjectId;
}

FieldName TES4HEDR::getName()
{
    return name;
}

float TES4HEDR::getVersion()
{
    return version;
}

int32_t TES4HEDR::getNumRecords()
{
    return numRecords;
}

uint32_t TES4HEDR::getNextObjectId()
{
    return nextObjectId;
}

TES4CNAM::TES4CNAM(QChar* inType, uint16_t inDataSize, QString inAuthor)
{
    setType(inType);
    setDataSize(inDataSize);
    author = inAuthor;

    FieldName inName = FieldName::Author_Information;
    setName(inName);
}

TES4CNAM::~TES4CNAM() { }

void TES4CNAM::setName(FieldName inName)
{
    name = inName;
}

void TES4CNAM::setAuthor(QString inAuthor)
{
    author = inAuthor;
}

FieldName TES4CNAM::getName()
{
    return name;
}

QString TES4CNAM::getAuthor()
{
    return author;
}

TES4INTV::TES4INTV(QChar* inType, uint16_t inDataSize, uint32_t inVersion)
{
    setType(inType);
    setDataSize(inDataSize);
    internalVersion = inVersion;

    FieldName inName = FieldName::Internal_Version;
    setName(inName);
}

TES4INTV::~TES4INTV() { }

void TES4INTV::setName(FieldName inName)
{
    name = inName;
}

void TES4INTV::setInternalVersion(uint32_t inVersion)
{
    internalVersion = inVersion;
}

FieldName TES4INTV::getName()
{
    return name;
}

uint32_t TES4INTV::getInternalVersion()
{
    return internalVersion;
}
