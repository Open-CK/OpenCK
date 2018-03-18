/*
** classform.cpp
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
** Created Date: 17-Oct-2017
*/

#include <data/records/classform.h>
#include <io/parser.h>

namespace esx
{
    /**
     * Create a new form by copying an existing header.
     * @brief Create a new form from header.
     * @param f Form header read by parser.
     */
    ClassForm::ClassForm(const Form &f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::Class);
    }

    /**
     * Loads the GMST header from the data stream.
     * @brief Loads the header.
     * @param r Reader object that performs all parsing functions.
     */
    void ClassForm::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch(h.type) {
                case 'EDID':
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length();
                    break;
                case 'FULL': {
                    if (r.isLocalizationEnabled()) {
                        // TODO: Implement proper localization handling.
                        this->setFullName(QString::number(r.read<quint32>(), 16));
                        read +=sizeof(quint32);
                    } else {
                        this->setFullName(r.readZstring());
                        read += this->getFullName().size();
                    }
                    break;
                }
                case 'DESC': {
                    if (r.isLocalizationEnabled()) {
                        this->setDesc(QString::number(r.read<quint32>(), 16));
                        read += sizeof(quint32);
                    } else {
                        this->setDesc(r.readZstring());
                        read += this->getDesc().size();
                    }
                    break;
                }
                case 'ICON':
                    this->setIcon(r.readZstring());
                    read += this->getIcon().length() + 1;
                    break;
                case 'DATA':
                    this->setClassData(r.read<ClassInf>());
                    read += sizeof(ClassInf);
                    break;
            }
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void ClassForm::addForm()
    {
        connect(this, &ClassForm::addCLAS,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertCLAS);
        emit addCLAS(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void ClassForm::readForm()
    {
        connect(this, &ClassForm::readCLAS,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readCLAS);
        emit readCLAS(*this);
    }
}
