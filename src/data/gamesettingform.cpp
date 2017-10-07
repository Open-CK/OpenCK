/*
** gmstform.cpp
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

#include "gamesettingform.h"

namespace esx
{
    GameSettingForm::GameSettingForm(const Form &formHeader)
    {
        name = FormName::GameSetting;
        header = formHeader.getHeader();
    }

    /**
     * Loads the form from the data stream.
     * @brief Loads the form.
     * @param in The data stream to load the file from.
     * @param fileNumber Number of file in list of files to load (0-indexed).
     */
    void GameSettingForm::load(QDataStream *in, int counter)
    {
        QByteArray buffer;

        quint32 temp = 0;
        readSubrecord(in, &temp);
        this->EditorID = io::ReadFile::readString(in, &buffer);
        readSubrecord(in, &temp);
        char ident = this->EditorID.toLower().at(0).toLatin1();

        if (ident == 'b' || ident == 'i') {
            this->ValueUInt = io::ReadFile::readUInt32(in, &buffer);
        } else if (ident == 'f') {
            this->ValueFloat = io::ReadFile::readFloat(in, &buffer);
        } else if (ident == 's') {
            //TODO: Implement lstring check
            quint32 index = io::ReadFile::readUInt32(in, &buffer);
            QString lstring = io::ReadFile::lookupString("Skyrim.esm", index,
                header.getType(), 'DATA');
        }
    }
}
