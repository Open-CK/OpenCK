/*
** form.cpp
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

#include "form.h"

//!@file form.cpp Source for parsing Forms from .esm and .esp files.

/**
 * Reads subrecord header values from a QDataStream.
 * @brief Reads a subrecord header.
 * @param in QDataStream to read from
 * @param read Integer representing the amount of bytes read.
 * @return Subrecord header.
 */
SubrecordHeader Form::readSubrecord(QDataStream* in, quint32* read)
{
    QByteArray buffer;
    SubrecordHeader header;
    quint32 type = ReadFile::readUInt32(in, &buffer);
    header.type = qToBigEndian(type);
    header.size = ReadFile::readUInt16(in, &buffer);
    *(read) += 6;

    if (header.type == 'XXXX') {
        header.size = ReadFile::readUInt32(in, &buffer);
        header.type = ReadFile::readUInt32(in, &buffer);
        ReadFile::readUInt16(in, &buffer);
        *(read) += 10;
    }

    return header;
}

void Form::readHeader(QDataStream *in, quint32 type)
{
    QByteArray buffer;

    header.type = type;
    header.dataSize = ReadFile::readUInt32(in, &buffer);
    header.flags = ReadFile::readUInt32(in, &buffer);
    header.id = ReadFile::readUInt32(in, &buffer);
    header.revision = ReadFile::readUInt32(in, &buffer);
    header.version = ReadFile::readUInt16(in, &buffer);
    header.unknown = ReadFile::readUInt16(in, &buffer);
}

quint32 Form::getType() const
{
    return header.type;
}

/**
 * The size of the form.
 * @brief The size of the form.
 * @return The size of the form.
 */
quint32 Form::getSize() const
{
    return header.dataSize + HEADER_SIZE; //Size of data fields + header size
}

quint32 Form::getFlags() const
{
    return header.flags;
}

quint32 Form::getId() const
{
    return header.id;
}

quint32 Form::getRevision() const
{
    return header.revision;
}

quint32 Form::getVersion() const
{
    return header.version;
}

quint32 Form::getUnknown() const
{
    return header.unknown;
}

FormHeader Form::getHeader() const
{
    return header;
}

void Form::setType(const quint32 type)
{
    header.type = type;
}

bool Form::setSize(const quint32 size)
{
    if (size > 0) {
        header.dataSize = size;
        return true;
    }
    return false;
}

void Form::setFlags(const quint32 flags)
{
    header.flags = flags;
}

void Form::setID(const quint32 id)
{
    header.id = id;
}

void Form::setRevision(const quint32 revision)
{
    header.revision = revision;
}

void Form::setVersion(const quint32 version)
{
    header.version = version;
}

void Form::setUnknown(const quint32 unknown)
{
    header.unknown = unknown;
}
