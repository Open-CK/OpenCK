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

#include "recordparent.h"

RecordParent::RecordParent() { }

RecordParent::~RecordParent() { }

void RecordParent::setDataSize(uint32_t inDataSize)
{
    dataSize = inDataSize;
}

void RecordParent::setFlags(uint32_t inFlags)
{
    flags = inFlags;
}

void RecordParent::setId(uint32_t inId)
{
    id = inId;
}

void RecordParent::setRevision(uint32_t inRevision)
{
    revision = inRevision;
}

void RecordParent::setType(QChar* inType)
{
    for (int i = 0; i < 4; i ++) {
        type[i] = *(inType);
        inType++;
    }
}

void RecordParent::setUnknown(uint16_t inUnknown)
{
    unknown = inUnknown;
}

void RecordParent::setVersion(uint32_t inVersion)
{
    version = inVersion;
}

uint32_t RecordParent::getDataSize()
{
    return dataSize;
}

uint32_t RecordParent::getFlags()
{
    return flags;
}

uint32_t RecordParent::getId()
{
    return id;
}

uint32_t RecordParent::getRevision()
{
    return revision;
}

QChar* RecordParent::getType()
{
    return type;
}

uint16_t RecordParent::getUnknown()
{
    return unknown;
}

uint32_t RecordParent::getVersion()
{
    return version;
}
