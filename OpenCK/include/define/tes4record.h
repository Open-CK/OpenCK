/*
** tes4record.h
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

#ifndef TES4RECORD_H
#define TES4RECORD_H

#include <QString>
#include <QMap>

#include "recordparent.h"
#include "fieldparent.h"

namespace Define
{
    class TES4Record;
    class TES4HEDR;
    class TES4CNAM;
    class TES4INTV;
}

/****************************************/
/* HEDR Subrecord, child of FieldParent */
/****************************************/

class TES4HEDR : public FieldParent
{
public:
    TES4HEDR(QChar* inType, uint16_t inDataSize, float inVersion,
              int32_t inNumRecords, uint32_t inNextObjectId);
    ~TES4HEDR();

    // Setter methods
    void setName(FieldName inName);
    void setVersion(float inVersion);
    void setNumRecords(int32_t inNumRecords);
    void setNextObjectId(uint32_t inNextObjectId);

    // Getter methods
    FieldName getName();
    float getVersion();
    int32_t getNumRecords();
    uint32_t getNextObjectId();

private:
    FieldName name;
    float version;
    int32_t numRecords;
    uint32_t nextObjectId;
};

/****************************************/
/* CNAM Subrecord, child of FieldParent */
/****************************************/

class TES4CNAM : public FieldParent
{
public:
    TES4CNAM(QChar* inType, uint16_t inDataSize, QString inAuthor);
    ~TES4CNAM();

    // Setter methods
    void setName(FieldName inName);
    void setAuthor(QString inAuthor);

    // Getter methods
    QString getAuthor();
    FieldName getName();

private:
    FieldName name;
    QString author;
};

/****************************************/
/* INTV Subrecord, child of FieldParent */
/****************************************/

class TES4INTV : public FieldParent
{
public:
    TES4INTV(QChar* inType, uint16_t inDataSize, uint32_t inVersion);
    ~TES4INTV();

    // Setter methods
    void setName(FieldName inName);
    void setInternalVersion(uint32_t inVersion);

    // Getter methods
    FieldName getName();
    uint32_t getInternalVersion();

private:
    FieldName name;
    uint32_t internalVersion;
};

/***************************************************************************/
/* TES4Record, child of RecordParent. Contains subrecords as data members. */
/***************************************************************************/

class TES4Record : public RecordParent
{
public:
    TES4Record();
    ~TES4Record();

    // Setter methods
    void setName(RecordName name);
    void setHEDR(TES4HEDR* inHEDR);
    void setCNAM(TES4CNAM* inCNAM);
    void setINTV(TES4INTV* inINTV);

    // Getter methods
    RecordName getName();
    TES4HEDR* getHEDR();
    TES4CNAM* getCNAM();
    TES4INTV* getINTV();

private:
    RecordName name;
    TES4HEDR* HEDR;
    TES4CNAM* CNAM;
    TES4INTV* INTV;
};

#endif // TES4RECORD_H
