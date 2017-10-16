/*
** globalvariableform.cpp
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
** Created Date: 16-Oct-2017
*/

#include "globalvariableform.h"
#include "parser.h"

namespace esx
{
    GlobalVariableForm::GlobalVariableForm(const Form& f)
    {
        this->header = f.getHeader();
        this->header.setName(FormName::GlobalVariable);
    }

    void GlobalVariableForm::load(io::Reader &r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch(h.type) {
                case 'EDID':
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length();
                    break;
                case 'FNAM':
                    this->setType(r.read<char>());
                    read += 1;
                    break;
                case 'FLTV':
                    this->setValue(r.read<float>());
                    read += 4;
                    break;
            }
        }
    }

    void GlobalVariableForm::addForm()
    {
        connect(this, &GlobalVariableForm::addGLOB,
                &io::Parser::getParser().getFileModel(), &models::FileModel::insertGLOB);
        emit addGLOB(*this);
    }

    void GlobalVariableForm::readForm()
    {
        connect(this, &GlobalVariableForm::readGLOB,
                &io::Parser::getParser().getFormModel(), &models::FormModel::readGLOB);
        emit readGLOB(*this);
    }
}
