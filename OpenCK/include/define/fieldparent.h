/*
** fieldparent.h
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

#ifndef FIELDPARENT_H
#define FIELDPARENT_H

#include <stdint.h>
#include <QString>
#include <QChar>
#include <array>

namespace Define
{
    class FieldParent;
    enum class FieldName;
}

enum class FieldName
{
    Header_Data, Author_Information, Description, Master_Files,
    Overriden_Forms, Internal_Version, Unknown_Value
};

class FieldParent
{
public:
    FieldParent();
    virtual ~FieldParent() = 0;

    // Setter methods
    virtual void setName(FieldName inName) = 0;
    void setType(QChar* inType);
    void setDataSize(uint16_t inDataSize);

    // Getter methods
    virtual FieldName getName() = 0;
    QChar* getType();
    uint16_t getDataSize();

private:
    QChar type[4];
    uint16_t dataSize;
};

#endif // FIELD_H
