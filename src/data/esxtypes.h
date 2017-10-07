/*
** esxtyped.h
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
** Created Date: 07-Oct-2017
*/

#ifndef ESXTYPES_H
#define ESXTYPES_H

#include <QtGlobal>

namespace esx
{
    /*
     * Define type aliases to reflect TES wiki,
     * for ease of reference
    */

    //Integer types
    typedef qint8 int8;
    typedef quint8 uint8;
    typedef qint16 int16;
    typedef quint16 uint16;
    typedef qint32 int32;
    typedef quint32 uint32;
    typedef qint64 int64;
    typedef quint64 uint64;

    //Floating-point
    typedef float float32;
    typedef double float64;

    //Esx-specific aliases
    typedef quint32 formid;
    typedef quint32 iref; //FormID index number
    typedef RgbStruct rgb;
    typedef quint64 hash; //BSA hash

    //String types
    typedef quint32 stringid; //IDs for strings file index
    typedef quint32 lstring;
    typedef quint32 dlstring;
    typedef quint32 ilstring;
    typedef ByteStringStruct bstring;  //Will have different io behaviours
    typedef ByteStringStruct bzstring; //Zero-terminated
    typedef ShortStringStruct wstring;
    typedef ShortStringStruct wzstring; //Zero-terminated
    typedef QString zstring; //Zero-terminated
    typedef QString string;

    //Data structures
    struct RgbStruct
    {
        uint8 red;
        uint8 green;
        uint8 blue;
        uint8 unknown_alpha;
    };

    struct ByteStringStruct
    {
        uint8 length;
        QString string;
    };

    struct ShortStringStruct
    {
        uint16 length;
        QString string;
    };
}

#endif // ESXTYPES_H
