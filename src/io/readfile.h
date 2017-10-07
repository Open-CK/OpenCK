/*
** readbytes.h
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

//!@file readfile.h Header for data being read from the file stream.

#ifndef READFILE_H
#define READFILE_H

#include <stdint.h>
#include <QDataStream>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

namespace esx
{
    /**
     * Static class from which files are read.
     * @brief Static class from which files are read.
     */
    class ReadFile
    {
    public:
        ReadFile();
        static QString readString(QDataStream* in, QByteArray* buffer);
        static char* readType(QDataStream* in, QByteArray* buffer);
        static quint8 readUByte(QDataStream* in, QByteArray* buffer);
        static qint32 readInt32(QDataStream* in, QByteArray* buffer);
        static quint32 readUInt32(QDataStream* in, QByteArray* buffer);
        static quint16 readUInt16(QDataStream* in, QByteArray* buffer);
        static quint64 readUInt64(QDataStream* in, QByteArray* buffer);
        static float readFloat(QDataStream* in, QByteArray* buffer);
        static QString lookupString(QString filename, quint32 index, quint32 recordType, quint32 subrecord);

    private:
        static quint8 getUByte(QByteArray* array);
        static qint32 getInt32(QByteArray* array);
        static quint32 getUInt32(QByteArray* array);
        static quint16 getUInt16(QByteArray* array);
        static quint64 getUInt64_t(QByteArray* array);
        static float getFloat(QDataStream* arrayStream);
    };
}

#endif // READFILE_H
