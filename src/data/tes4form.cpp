/*
** tes4record.cpp
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

#include "tes4form.h"

//!@file tes4form.cpp The header form.

TES4Form::TES4Form(const Form &formHeader)
{
    name = FormName::TES4;
    header = formHeader.getHeader();
}

/**
 * Destructs header object in memory.
 * @brief Destructs header object.
 */
TES4Form::~TES4Form() { }

/**
 * Loads the TES4 header from the data stream.
 * @brief Loads the header.
 * @param in The data stream to load the file from.
 * @param fileNumber Number of file in list of files to load (0-indexed).
 */
void TES4Form::load(QDataStream* in, int fileNumber)
{
    QByteArray buffer;

    quint32 read = 0;
    while (read < header.getDataSize()) {
        SubrecordHeader sHeader = readSubrecord(in, &read);

        switch (sHeader.type) {
            case 'HEDR':
                this->Version = ReadFile::readFloat(in, &buffer);
                this->NumRecords = ReadFile::readUInt32(in, &buffer);
                this->NextID = ReadFile::readUInt32(in, &buffer);
                read += 12;

                break;
            case 'CNAM':
                this->Author = ReadFile::readString(in, &buffer);
                read += (this->Author.length() + 1);

                break;
            case 'SNAM':
                this->Desc = ReadFile::readString(in, &buffer);
                read += (this->Desc.length() + 1);

                break;
            case 'MAST': {
                QString name = ReadFile::readString(in, &buffer);
                read += (name.length() + 1);
                SubrecordHeader dataH = readSubrecord(in, &read);
                quint64 data = ReadFile::readUInt64(in, &buffer);
                read += 8;
                this->Masters.insert(name, data);

                break;
            }
            case 'ONAM': {
                quint16 onamSize = 0;

                while (onamSize < sHeader.size) {
                    quint32 onamType = ReadFile::readUInt32(in, &buffer);
                    this->Overrides.append(onamType);
                    onamSize += 4;
                }
                read += (onamSize);

                break;
            }
            case 'INTV':
                this->Intv = ReadFile::readUInt32(in, &buffer);
                read += 4;

                break;
            case 'INCC':
                this->Incc = ReadFile::readUInt32(in, &buffer);
                read += 4;

                break;
        }
    }
}
