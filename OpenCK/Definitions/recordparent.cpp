/*
** parsed.cpp
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

RecordParent::RecordParent() {}

RecordParent::~RecordParent() {}

/**
 * Returns a pointer to the start of a character array that contains the record's type code.
 * @brief RecordParent::getType
 * @return
 */
char* RecordParent::getType()
{
    return type;
}

/**
 * Returns the dataSize of the record.
 * @brief RecordParent::getDataSize
 * @return
 */
uint32_t RecordParent::getDataSize()
{
    return dataSize;
}

/**
 * Returns the record flags.
 * @brief RecordParent::getFlags
 * @return
 */
uint32_t RecordParent::getFlags()
{
    return flags;
}

/**
 * Returns the record ID.
 * @brief RecordParent::getId
 * @return
 */
uint32_t RecordParent::getId()
{
    return id;
}

/**
 * Returns the Revision Number of the record (unknown purpose, need for writing).
 * @brief RecordParent::getRevision
 * @return
 */
uint32_t RecordParent::getRevision()
{
    return revision;
}

/**
 * Returns the Version Number of the record (unknown purpose, need for writing).
 * @brief RecordParent::getVersion
 * @return
 */
uint32_t RecordParent::getVersion()
{
    return version;
}

/**
 * Returns the record's 'Unknown' property (unknown purpose, need for writing).
 * @brief RecordParent::getUnknown
 * @return
 */
uint16_t RecordParent::getUnknown()
{
    return unknown;
}

/**
 * Returns a pointer to the start of the record data array.
 * @brief RecordParent::getData
 * @return
 */
uint8_t* RecordParent::getData()
{
    return data;
}
