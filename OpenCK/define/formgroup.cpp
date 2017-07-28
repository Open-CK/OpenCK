/*
** formgroup.cpp
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
** Created Date: 28-Jul-2017
*/

#include "formgroup.h"

/**
 * Initialise a new group with corresponding necessary information.
 * @brief Create a new group.
 * @param in File stream.
 * @param buffer Buffer to populate with temporary data.
 */
FormGroup::FormGroup(QDataStream *in, QByteArray *buffer) : groupType(Type::New), groupSize(0), groupLabel(0)
{
    //"GRUP" already read by parser.cpp
    groupSize = ReadFile::readUInt32(in, buffer);
    groupLabel = qToBigEndian(ReadFile::readUInt32(in, buffer));
    groupType = static_cast<Type>(ReadFile::readInt32(in, buffer));

    //Skip past unnecessary values
    for (int i = 0; i < 4; ++i) {
        ReadFile::readUInt16(in, buffer);
    }
}

/**
 * Redirect to appropriate loading method based on group type.
 * @brief Load a group.
 */
void FormGroup::load()
{
    switch (groupType) {
        case Type::Top:
            loadTop();
            break;
        //TODO: Populate with other group types when approached
    }
}

/**
 * Load a top group (group of similar forms).
 * @brief Load a top group.
 */
void FormGroup::loadTop()
{
    //TODO: write function to load forms in top group
}
