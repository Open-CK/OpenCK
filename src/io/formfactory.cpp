/*
** formfactory.cpp
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
** Created Date: 06-Oct-2017
*/

#include <io/formfactory.h>

namespace io
{
    /**
     * Create a new form using the header read by the parser.
     * @brief Create appropriate new forms.
     * @param formHeader Form header read by parser, containing type code.
     * @param r Provides raw data read functionality.
     * @return Appropriate form subclass to parser.
     */
    esx::Form *FormFactory::createForm(const esx::Form& formHeader, Reader& r)
    {
        esx::Form *newForm{ nullptr };

        switch(formHeader.getHeader().getType()) {
            case 'TES4':
                newForm = new esx::TES4Form(formHeader);
                break;
            case 'GMST':
                newForm = new esx::GameSettingForm(formHeader);
                break;
            case 'KYWD':
            case 'LCRT':
            case 'AACT':
                newForm = new esx::RgbForm(formHeader);
                break;
            case 'TXST':
                newForm = new esx::TextureSetForm(formHeader);
                break;
            case 'GLOB':
                newForm = new esx::GlobalVariableForm(formHeader);
                break;
            case 'CLAS':
                newForm = new esx::ClassForm(formHeader);
                break;
            case 'FACT':
                newForm = new esx::FactionForm(formHeader);
                break;
            case 'EYES':
                newForm = new esx::EyesForm(formHeader);
                break;
            case 'SOUN':
                newForm = new esx::SoundForm(formHeader);
                break;
            case 'ASPC':
                newForm = new esx::AcousticSpaceForm(formHeader);
                break;
            case 'MESG':
                newForm = new esx::MessageForm(formHeader);
            default:
                break;
        }

        if (newForm != nullptr) {
            newForm->load(r);
        }
        return newForm;
    }
}
