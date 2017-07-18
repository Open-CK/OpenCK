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

#ifndef READFILE_H
#define READFILE_H

#include <stdint.h>
#include <QDataStream>

class ReadFile
{
public:
    ReadFile();
    static QString readString(QDataStream* in, QByteArray* buffer);
    static char* readChar(QDataStream* in, QByteArray* buffer);
	static qint32 readInt32_t(QDataStream* in, QByteArray* buffer);
	static quint32 readUInt32_t(QDataStream* in, QByteArray* buffer);
	static quint16 readUInt16_t(QDataStream* in, QByteArray* buffer);
	static quint64 readUInt64_t(QDataStream* in, QByteArray* buffer);
    static float readFloat(QDataStream* in, QByteArray* buffer);

private:
	static qint32 getInt32_t(QByteArray* array);
	static quint32 getUInt32_t(QByteArray* array);
	static quint16 getUInt16_t(QByteArray* array);
	static quint64 getUInt64_t(QByteArray* array);
    static float getFloat(QDataStream* arrayStream);
};

#endif // READFILE_H
