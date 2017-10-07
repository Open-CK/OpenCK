/*
** colorform.cpp
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
** Created Date: 14-Aug-2017
*/

#include "colorform.h"

ColorForm::ColorForm(const Form &formHeader)
{
    header = formHeader.getHeader();

    switch(header.getType()) {
        case 'KYWD':
            name = FormName::Keyword;
            break;
        case 'LCRT':
            name = FormName::LocationReferenceType;
            break;
        case 'AACT':
            name = FormName::Action;
            break;
    }
}

/**
 * Loads the form from the data stream.
 * @brief Loads the form.
 * @param in The data stream to load the file from.
 * @param fileNumber Number of file in list of files to load (0-indexed).
 */
void ColorForm::load(QDataStream *in, int fileNumber)
{
    QByteArray buffer;

    quint32 temp = 0;
    readSubrecord(in, &temp);
    this->EditorID = ReadFile::readString(in, &buffer);

    //This was breaking things, conditional stopped it
    //For some reason, some records don't contain an RGB value, just a header?!
    if (quint32((this->EditorID.length() + 1) + 6) < header.getDataSize()) {
        readSubrecord(in, &temp);
        this->Rgb = ReadFile::readUInt32(in, &buffer);
    }
}
