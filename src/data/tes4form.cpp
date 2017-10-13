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
#include "parser.h"

//!@file tes4form.cpp The header form.

namespace esx
{
    /**
     * Create a new form by copying an existing header.
     * @brief Create a new form from header.
     * @param formHeader Form header read by parser.
     */
    TES4Form::TES4Form(const Form &f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::TES4);
    }

    /**
     * Loads the TES4 header from the data stream.
     * @brief Loads the header.
     * @param in The data stream to load the file from.
     * @param fileNumber Number of file in list of files to load (0-indexed).
     */
    void TES4Form::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
                case 'HEDR':
                    this->Version = r.read<float>();
                    this->NumRecords = r.read<quint32>();
                    this->NextID = r.read<quint32>();
                    read += 12;
                    break;
                case 'CNAM':
                    this->Author = r.readZstring();
                    read += (this->Author.length() + 1);
                    break;
                case 'SNAM':
                    this->Desc = r.readZstring();
                    read += (this->Desc.length() + 1);
                    break;
                case 'MAST': {
                    QString name = r.readZstring();
                    read += (name.length() + 1);
                    readSubrecord(r, &read);
                    quint64 data = r.read<quint64>();
                    read += 8;
                    this->Masters.insert(name, data);
                    break;
                }
                case 'ONAM': {
                    quint16 onamSize = 0;

                    while (onamSize < h.size) {
                        quint32 onamType = r.read<quint32>();
                        this->Overrides.append(onamType);
                        onamSize += 4;
                    }

                    read += (onamSize);
                    break;
                }
                case 'INTV':
                    this->Intv = r.read<quint32>();
                    read += 4;
                    break;
                case 'INCC':
                    this->Incc = r.read<quint32>();
                    read += 4;
                    break;
            }
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void TES4Form::addForm()
    {
        connect(this, &TES4Form::addTES4,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertTES4);
        emit addTES4(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void TES4Form::readForm()
    {
        connect(this, &TES4Form::readTES4,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readTES4);
        emit readTES4(*this);
    }
}
