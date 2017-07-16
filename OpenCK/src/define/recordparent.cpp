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

/**
 * Set the size of data (in bytes) in the record.
 * @brief RecordParent::setDataSize
 * @param inDataSize Data size in bytes.
 */
void RecordParent::setDataSize(uint32_t inDataSize)
{
    dataSize = inDataSize;
}

/**
 * Set the record flags.
 * @brief RecordParent::setFlags
 * @param inFlags Record flags.
 */
void RecordParent::setFlags(uint32_t inFlags)
{
    flags = inFlags;
}

/**
 * Set the record ID.
 * @brief RecordParent::setId
 * @param inId Record ID.
 */
void RecordParent::setId(uint32_t inId)
{
    id = inId;
}

/**
 * Set the record Revision number (unknown integer).
 * @brief RecordParent::setRevision
 * @param inRevision Revision number (unknown integer).
 */
void RecordParent::setRevision(uint32_t inRevision)
{
    revision = inRevision;
}

/**
 * Set the 4-character record type code.
 * @brief RecordParent::setType
 * @param inType 4-character type code.
 */
void RecordParent::setType(QChar* inType)
{
    for (int i = 0; i < 4; i ++) {
        type[i] = *(inType);
        inType++;
    }
}

/**
 * Set unknown integer value.
 * @brief RecordParent::setUnknown
 * @param inUnknown Unknown integer.
 */
void RecordParent::setUnknown(uint16_t inUnknown)
{
    unknown = inUnknown;
}

/**
 * Set the record version (unknown integer).
 * @brief RecordParent::setVersion
 * @param inVersion Record version (unknown integer).
 */
void RecordParent::setVersion(uint32_t inVersion)
{
    version = inVersion;
}

/**
 * Retrieve size of data (in bytes) of record.
 * @brief RecordParent::getDataSize
 * @return
 */
uint32_t RecordParent::getDataSize()
{
    return dataSize;
}

/**
 * Retrieve flags of record.
 * @brief RecordParent::getFlags
 * @return Record flags.
 */
uint32_t RecordParent::getFlags()
{
    return flags;
}

/**
 * Retrieve record ID.
 * @brief RecordParent::getId
 * @return Record ID.
 */
uint32_t RecordParent::getId()
{
    return id;
}

/**
 * Retrieve revision number (unknown integer).
 * @brief RecordParent::getRevision
 * @return Revision number (unknown integer).
 */
uint32_t RecordParent::getRevision()
{
    return revision;
}

/**
 * Retrieve 4-character type code.
 * @brief RecordParent::getType
 * @return 4-character type code.
 */
QChar* RecordParent::getType()
{
    return type;
}

/**
 * Retrieve unknown integer value.
 * @brief RecordParent::getUnknown
 * @return Unknown integer.
 */
uint16_t RecordParent::getUnknown()
{
    return unknown;
}

/**
 * Retrieve version of record (unknown integer).
 * @brief RecordParent::getVersion
 * @return Record version (unknown integer).
 */
uint32_t RecordParent::getVersion()
{
    return version;
}
