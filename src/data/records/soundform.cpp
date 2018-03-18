/*
** soundform.cpp
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
** Created Date: 18-Mar-2017
*/

#include <data/records/soundform.h>
#include <io/parser.h>

namespace esx
{
    /**
    * Create a new form by copying an existing header.
    * @brief Create a new form from header.
    * @param f Form header read by parser.
    */
    SoundForm::SoundForm(const Form &f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::Sound);
    }

    /**
     * Loads the SOUN information from the data stream.
     * @brief Loads the record.
     * @param r Reader object that performs all parsing functions.
     */
    void SoundForm::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
                case 'EDID':
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length();
                    break;
                // Object Bounds field
                case 'OBND':
                    this->setObjectBounds(r.read<ObjectBoundsField>());
                    read += sizeof(ObjectBoundsField);
                    break;
                // Legacy, .wav path. Unneeded, stored in SNDR record
                case 'FNAM': {
                    QString temp = r.readZstring();
                    read += temp.length();
                    break;
                }
                // Legacy 36-byte struct, unneeded
                case 'SNDD':
                    read += 36;
                    break;
                // FormID of associated SNDR record
                case 'SDSC':
                    this->setSoundDataID(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
            }
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void SoundForm::addForm()
    {
        connect(this, &SoundForm::addSOUN,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertSOUN);
        emit addSOUN(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void SoundForm::readForm()
    {
        connect(this, &SoundForm::readSOUN,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readSOUN);
        emit readSOUN(*this);
    }
}
