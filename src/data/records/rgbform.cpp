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

#include "rgbform.h"
#include "parser.h"

namespace esx
{
    /**
     * Create a new form by copying an existing header.
     * @brief Create a new form from header.
     * @param f Form header read by parser.
     */
    RgbForm::RgbForm(const Form& f)
    {
        header = f.getHeader();

        switch(header.getType()) {
            case 'KYWD':
                this->header.setName(FormName::Keyword);
                break;
            case 'LCRT':
                this->header.setName(FormName::LocationReferenceType);
                break;
            case 'AACT':
                this->header.setName(FormName::Action);
                break;
        }
    }

    /**
     * Loads the RGB header from the data stream.
     * @brief Loads the header.
     * @param r Reader object that performs all parsing functions.
     */
    void RgbForm::load(io::Reader& r)
    {
        quint32 temp = 0;
        readSubrecord(r, &temp);
        this->EditorID = r.readZstring();

        if (quint32((this->EditorID.length() + 1) + 6) < header.getDataSize()) {
            readSubrecord(r, &temp);
            this->Rgb = r.read<quint32>();
        }
    }

    /**
     * Signal. Add the form to the file model.
     * @brief Add form to file model.
     */
    void RgbForm::addForm()
    {
        connect(this, &RgbForm::addRGB,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertRGB);
        emit addRGB(*this);
    }

    /**
     * Signal. Display the contents of a form stored in the file model to the form model.
     * @brief Display contents in form model.
     */
    void RgbForm::readForm()
    {
        connect(this, &RgbForm::readRGB,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readRGB);
        emit readRGB(*this);
    }
}
