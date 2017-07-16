/*
** fieldparent.cpp
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

#include <fieldparent.h>

FieldParent::FieldParent() { }

FieldParent::~FieldParent() { }

/**
 * Set 4-character type code.
 * @brief FieldParent::setType
 * @param inType Pointer to first character of code.
 */
void FieldParent::setType(QChar* inType)
{
    for (int i = 0; i < 4; i ++) {
        type[i] = *(inType);
        inType++;
    }
}

/**
 * Set the size of the data contained in the field/subrecord.
 * @brief FieldParent::setDataSize
 * @param inDataSize Data size of field/subrecord in bytes.
 */
void FieldParent::setDataSize(uint16_t inDataSize)
{
    dataSize = inDataSize;
}

/**
 * Retrieve the 4-character type code.
 * @brief FieldParent::getType
 * @return Type code.
 */
QChar* FieldParent::getType()
{
    return type;
}

/**
 * Retrieve the size of the data contained in the field/subrecord.
 * @brief FieldParent::getDataSize
 * @return Data size of field/subrecord in bytes.
 */
uint16_t FieldParent::getDataSize()
{
    return dataSize;
}
