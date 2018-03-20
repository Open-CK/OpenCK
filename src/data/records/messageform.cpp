/*
** messageform.cpp
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
** Created Date: 20-Mar-2017
*/

#include <data/records/messageform.h>
#include <io/parser.h>

namespace esx
{
    /**
    * Create a new form by copying an existing header.
    * @brief Create a new form from header.
    * @param f Form header read by parser.
    */
    MessageForm::MessageForm(const Form &f) : MessageForm()
    {
        this->header = f.getHeader();
        this->header.setName(FormName::Message);
    }

    /**
    * Loads the MESG information from the data stream.
    * @brief Loads the record.
    * @param r Reader object that performs all parsing functions.
    */
    void MessageForm::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
            case 'EDID':
                this->setEditorID(r.readZstring());
                read += this->getEditorID().length();
                break;
                // Actual text displayed
            case 'DESC':
                if (r.isLocalizationEnabled()) { // TODO: Handle localized strings properly.
                    this->setMessageText(QString::number(r.read<quint32>(), 16));
                    read += sizeof(quint32);
                }
                else {
                    this->setMessageText(r.readZstring());
                    read += this->getMessageText().length();
                }
                break;
                // Optional category name
            case 'FULL':
                if (r.isLocalizationEnabled()) { // TODO: Handle localized strings properly.
                    this->setTitle(QString::number(r.read<quint32>(), 16));
                    read += sizeof(quint32);
                }
                else {
                    this->setTitle(r.readZstring());
                    read += this->getTitle().length();
                }
                break;
                // Always 0
            case 'INAM':
                this->setUnknown(r.read<quint32>());
                read += sizeof(quint32);
                break;
                // QUST FormID
            case 'QNAM':
                this->setQuestID(r.read<quint32>());
                read += sizeof(quint32);
                break;
                // Flags, 0x01 = Message Box, 0x02 = Auto-Display
            case 'DNAM':
                this->setFlags(r.read<quint32>());
                read += sizeof(quint32);
                break;
                // Display Time
            case 'TNAM':
                this->setTime(r.read<quint32>());
                read += sizeof(quint32);
                break;
                // TODO: Implement conditions. Skips for now.
            case 'CTDA': {
                qint64 readOffset = r.pos() + (header.getDataSize() - read);
                r.seek(readOffset);
                read = header.getDataSize();
                break; }
                // Response/Activation Text
            case 'ITXT':
                if (r.isLocalizationEnabled()) { // TODO: Handle localized strings properly.
                    this->setResponseText(QString::number(r.read<quint32>(), 16));
                    read += sizeof(quint32);
                }
                else {
                    this->setResponseText(r.readZstring());
                    read += this->getResponseText().length();
                }
                break;
            }
        }
    }

    /**
    * Signal. Add the form to the file model.
    * @brief Add form to file model.
    */
    void MessageForm::addForm()
    {
        connect(this, &MessageForm::addMESG,
            &io::Parser::getParser().getFileModel(), &models::FileModel::insertMESG);
        emit addMESG(*this);
    }

    /**
    * Signal. Display the contents of a form stored in the file model to the form model.
    * @brief Display contents in form model.
    */
    void MessageForm::readForm()
    {
        connect(this, &MessageForm::readMESG,
            &io::Parser::getParser().getFormModel(), &models::FormModel::readMESG);
        emit readMESG(*this);
    }
}
