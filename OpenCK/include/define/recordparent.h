/*
** recordparent.h
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

#ifndef RECORDPARENT_H
#define RECORDPARENT_H

#include <stdint.h>
#include <array>
#include <QChar>

namespace Define
{
    class RecordParent;
}

class RecordParent
{
public:
    RecordParent();    
    virtual ~RecordParent() = 0;

    // Setter methods
    void setType(QChar* inType);
    void setDataSize(uint32_t inDataSize);
    void setFlags(uint32_t inFlags);
    void setId(uint32_t inId);
    void setRevision(uint32_t inRevision);
    void setVersion(uint32_t inVersion);
    void setUnknown(uint16_t inUnknown);

    // Getter methods
    QChar* getType();
    uint32_t getDataSize();
    uint32_t getFlags();
    uint32_t getId();
    uint32_t getRevision();
    uint32_t getVersion();
    uint16_t getUnknown();

private:
    QChar type[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
    uint32_t version;
    uint16_t unknown;
};

#endif // RECORDPARENT_H
