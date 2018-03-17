/*
** eyesform.cpp
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

#include <data/records/eyesform.h>
#include <io/parser.h>

namespace esx
{
    /**
    * Create a new form by copying an existing header.
    * @brief Create a new form from header.
    * @param f Form header read by parser.
    */
    EyesForm::EyesForm(const Form &f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::Eyes);
    }

    /**
     * Loads the EYES information from the data stream.
     * @brief Loads the record.
     * @param r Reader object that performs all parsing functions.
     */
    void EyesForm::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
                case 'EDID':
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length();
                    break;
                case 'FULL': {
                    //TODO: Implement lstring check
                    quint32 index = r.read<quint32>();
                    QString lstring = r.lookupString("Skyrim.esm", index,
                        header.getType(), 'DATA');
                    read += sizeof(quint32);
                    break;
                }
                case 'ICON':
                    this->setIcon(r.readZstring());
                    read += this->getIcon().length();
                    break;
                case 'DATA':
                    this->setFlags(r.read<quint8>());
                    read += sizeof(quint8);
                    break;
            }
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void EyesForm::addForm()
    {
        connect(this, &EyesForm::addEYES,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertEYES);
        emit addEYES(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void EyesForm::readForm()
    {
        connect(this, &EyesForm::readEYES,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readEYES);
        emit readEYES(*this);
    }
}
