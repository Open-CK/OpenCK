/*
** formcomponents.h
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
** Created Date: 18-Oct-2017
*/

//!@file formcomponents.h Header for the abstract form class.

#ifndef FORMCOMPONENTS_H
#define FORMCOMPONENTS_H

#include <QMap>
#include <QString>

namespace esx
{
    /**
     * Generic flags found in record headers.
     * @brief Generic record flags.
     **/
    static QMap<quint32, QString> headerFlags {
        { 0x00000020, "Deleted" },
        { 0x00000040, "Constant" },
        { 0x00000100, "Must Update Animations"},
        { 0x00000400, "Quest Item/Persistent Reference"},
        { 0x00000800, "Initially Disabled" },
        { 0x00001000, "Ignored" },
        { 0x00008000, "Visible When Distant" },
        { 0x00040000, "Compressed Data" },
        { 0x00080000, "Cannot Wait" },
        { 0x00800000, "Marker" },
        { 0x04000000, "NavMesh Gen — Filter" },
        { 0x08000000, "NavMesh Gen — Bounding Box" },
        { 0x40000000, "NavMesh Gen — Ground"}
    };

    /**
     * String names of skills referred to by a skill index.
     * @brief Skill index/name array.
     **/
    static QString skillIndexes[18] {
        "One Handed",
        "Two Handed",
        "Marksman",
        "Block",
        "Smithing",
        "Heavy Armor",
        "Light Armor",
        "Pickpocket",
        "Lockpicking",
        "Sneak",
        "Alchemy",
        "Speechcraft",
        "Alteration",
        "Conjuration",
        "Destruction",
        "Illusion",
        "Restoration",
        "Enchanting"
    };
}

#endif // FORMCOMPONENTS_H
