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
#include "QVariant"
#include <QList>

#include "recordparent.h"
#include "hedrfield.h"
#include "cnamfield.h"
#include "intvfield.h"

namespace Define
{
    class TES4Record;
}

class TES4Record : public RecordParent
{
public:
    TES4Record();
    ~TES4Record();

    // Setter methods
    void setHEDR(HEDRField* inHEDR);
    void setCNAM(CNAMField* inCNAM);
    void setINTV(INTVField* inINTV);

    // Getter methods
    HEDRField* getHEDR();
    CNAMField* getCNAM();
    INTVField* getINTV();

private:
    HEDRField* HEDR;
    CNAMField* CNAM;
    INTVField* INTV;
};

#endif // TES4RECORD_H
