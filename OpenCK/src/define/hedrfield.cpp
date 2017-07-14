/*
** hedrfield.cpp
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

#include <hedrfield.h>

HEDRField::HEDRField(QChar *inType, uint16_t inDataSize, float inVersion,
                     int32_t inNumRecords, uint32_t inNextObjectId)
{
    setType(inType);
    setDataSize(inDataSize);
    version = inVersion;
    numRecords = inNumRecords;
    nextObjectId = inNextObjectId;
}

HEDRField::~HEDRField() { }

void HEDRField::setVersion(float inVersion)
{
    version = inVersion;
}

void HEDRField::setNumRecords(int32_t inNumRecords)
{
    numRecords = inNumRecords;
}

void HEDRField::setNextObjectId(uint32_t inNextObjectId)
{
    nextObjectId = inNextObjectId;
}

float HEDRField::getVersion()
{
    return version;
}

int32_t HEDRField::getNumRecords()
{
    return numRecords;
}

uint32_t HEDRField::getNextObjectId()
{
    return nextObjectId;
}
