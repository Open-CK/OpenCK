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

namespace esx
{
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
        quint32 type = io::ReadFile::readUInt32(in, &buffer);
        header.type = qToBigEndian(type);
        header.size = io::ReadFile::readUInt16(in, &buffer);
        *(read) += 6;

        if (header.type == 'XXXX') {
            header.size = io::ReadFile::readUInt32(in, &buffer);
            header.type = io::ReadFile::readUInt32(in, &buffer);
            io::ReadFile::readUInt16(in, &buffer);
            *(read) += 10;
        }

        return header;
    }

    void Form::readHeader(QDataStream *in, quint32 type)
    {
        QByteArray buffer;

        this->header.setType(type);
        this->header.setDataSize(io::ReadFile::readUInt32(in, &buffer));
        this->header.setFlags(io::ReadFile::readUInt32(in, &buffer));
        this->header.setID(io::ReadFile::readUInt32(in, &buffer));
        this->header.setRevision(io::ReadFile::readUInt32(in, &buffer));
        this->header.setVersion(io::ReadFile::readUInt16(in, &buffer));
        this->header.setUnknown(io::ReadFile::readUInt16(in, &buffer));
    }

    FormHeader Form::getHeader() const
    {
        return this->header;
    }

    /**
     * The size of the form.
     * @brief The size of the form.
     * @return The size of the form.
     */
    quint32 Form::getSize() const
    {
        return this->header.getDataSize() + 24; //Size of data fields + header size
    }
}
