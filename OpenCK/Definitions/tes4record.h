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
#include <QStringList>
#include "recordparent.h"

struct TES4Data
{
    typedef uint64_t formid;

    float version;
    int32_t numRecords;
    uint64_t nextObjectId;
    QString author;
    QString desc;
    QStringList masters;
    uint64_t fileSize;
    formid overrides[50];

    /* Unknown values, but they exist in the header nonetheless. */
    uint32_t intv;
    uint32_t incc;
};

typedef struct TES4Data TES4Data;

class TES4Record : public RecordParent
{
public:
    TES4Record();
    TES4Data data;
};

#endif // TES4RECORD_H
