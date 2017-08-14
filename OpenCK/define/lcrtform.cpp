/*
** kywdform.cpp
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
** Created Date: 05-Aug-2017
*/

#include "lcrtform.h"

void LCRTForm::load(QDataStream *in, int fileNumber)
{
    QByteArray buffer;

    header.type = qToBigEndian(ReadFile::readUInt32(in, &buffer));
    header.dataSize = ReadFile::readUInt32(in, &buffer);
    header.flags = ReadFile::readUInt32(in, &buffer);
    header.id = ReadFile::readUInt32(in, &buffer);
    header.revision = ReadFile::readUInt32(in, &buffer);
    header.version = ReadFile::readUInt16(in, &buffer);
    header.unknown = ReadFile::readUInt16(in, &buffer);

    quint32 temp = 0;
    readSubrecord(in, &temp);
    editorID = ReadFile::readString(in, &buffer);

    if (quint32((editorID.length() + 1) + 6) < header.dataSize) {
        readSubrecord(in, &temp);
        rgb = ReadFile::readUInt32(in, &buffer);
    }
}

QString LCRTForm::getEditorID() const
{
    return editorID;
}

quint32 LCRTForm::getRgb() const
{
    return rgb;
}

void LCRTForm::setEditorID(const QString in)
{
    editorID = in;
}

void LCRTForm::setRgb(const quint32 in)
{
    rgb = in;
}
