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

#include <data/records/gamesettingform.h>
#include <io/parser.h>

namespace esx
{
    /**
     * Create a new form by copying an existing header.
     * @brief Create a new form from header.
     * @param f Form header read by parser.
     */
    GameSettingForm::GameSettingForm(const Form &f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::GameSetting);
    }

    /**
     * Loads the GMST header from the data stream.
     * @brief Loads the header.
     * @param r Reader object that performs all parsing functions.
     */
    void GameSettingForm::load(io::Reader& r)
    {
        //EDID
        quint32 temp = 0;
        readSubrecord(r, &temp);
        this->EditorID = r.readZstring();

        //DATA
        readSubrecord(r, &temp);
        char ident = EditorID.toLower().at(0).toLatin1();

        if (ident == 'b' || ident == 'i') {
            this->ValueUInt = r.read<quint32>();
        }
        else if (ident == 'f') {
            this->ValueFloat = r.read<quint32>();
        }
        else if (ident == 's') {
            //TODO: Implement lstring check
            quint32 index = r.read<quint32>();
            QString lstring = r.lookupString("Skyrim.esm", index,
                header.getType(), 'DATA');
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void GameSettingForm::addForm()
    {
        connect(this, &GameSettingForm::addGMST,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertGMST);
        emit addGMST(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void GameSettingForm::readForm()
    {
        connect(this, &GameSettingForm::readGMST,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readGMST);
        emit readGMST(*this);
    }
}
