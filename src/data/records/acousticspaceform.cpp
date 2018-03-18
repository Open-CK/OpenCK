/*
** acousticspaceform.cpp
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

#include <data/records/acousticspaceform.h>
#include <io/parser.h>

namespace esx
{
    /**
    * Create a new form by copying an existing header.
    * @brief Create a new form from header.
    * @param f Form header read by parser.
    */
    AcousticSpaceForm::AcousticSpaceForm(const Form &f) : EditorID(""),
        ObjectBounds{0, 0, 0, 0, 0, 0}, AmbientSoundID(0), RegionSoundID(0), ReverbDataID(0)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::AcousticSpace);
    }

    /**
     * Loads the ASPC information from the data stream.
     * @brief Loads the record.
     * @param r Reader object that performs all parsing functions.
     */
    void AcousticSpaceForm::load(io::Reader& r)
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
                // FormID of associated SNDR, cell ambient sound
                case 'SNAM':
                    this->setAmbientSoundID(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                // FormID of associated REGN, region sound
                case 'RDAT':
                    this->setRegionSoundID(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                // FormID of associated REVB, cell reverb
                case 'BNAM':
                    this->setReverbDataID(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
            }
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void AcousticSpaceForm::addForm()
    {
        connect(this, &AcousticSpaceForm::addASPC,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertASPC);
        emit addASPC(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void AcousticSpaceForm::readForm()
    {
        connect(this, &AcousticSpaceForm::readASPC,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readASPC);
        emit readASPC(*this);
    }
}
