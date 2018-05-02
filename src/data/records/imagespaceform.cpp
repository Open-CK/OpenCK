/*
** imagespaceform.cpp
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
** Created Date: 02-May-2018
*/

#include <data/records/imagespaceform.h>
#include <io/parser.h>

namespace esx
{
    ImagespaceForm::ImagespaceForm(const Form& form)
        : ImagespaceForm()
    {
        this->header = form.getHeader();
        this->header.setName(FormName::Imagespace);
    }

    void ImagespaceForm::load(io::Reader& r)
    {
        quint32 read{ 0 };
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
            case 'EDID': // Editor ID
                this->setEditorID(r.readZstring());
                read += this->getEditorID().length();
                break;
            case 'ENAM':
                break;
            case 'HNAM': // HDR params

                break;
            case 'CNAM': // Cinematic params
                break;
            case 'TNAM': // Tint params
                break;
            case 'DNAM': // Depth of Field params
                break;
            }
        }
    }

    void ImagespaceForm::addForm()
    {
        connect(this, &ImagespaceForm::addIMGS,
            &io::Parser::getParser().getFileModel(), &models::FileModel::insertIMGS);
        emit addIMGS(*this);
    }

    void ImagespaceForm::readForm()
    {
        connect(this, &ImagespaceForm::readIMGS,
            &io::Parser::getParser().getFormModel(), &models::FormModel::readIMGS);
        emit readIMGS(*this);
    }
}