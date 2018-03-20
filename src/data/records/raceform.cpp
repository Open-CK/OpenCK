/*
** raceform.cpp
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
** Created Date: 19-Mar-2018
*/

#include <data/records/raceform.h>

namespace esx
{
    RaceForm::RaceForm(const Form& form)
    {
        this->header = form.getHeader();
        this->header.setName(FormName::Race);
    }

    void RaceForm::load(io::Reader& r)
    {
        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
            case 'EDID': // Editor ID
                this->setEditorID(r.readZstring());
                read += this->getEditorID().length();
                break;
            // Full name
            case 'FULL': {

                if (r.isLocalizationEnabled()) { // TODO: Handle localized strings properly.
                    this->setFullName(QString::number(r.read<quint32>(), 16));
                    read += sizeof(quint32);
                }
                else {
                    this->setFullName(r.readZstring());
                    read += this->getFullName().length();
                }
                break;
            }
            // Description
            case 'DESC': {

                if (r.isLocalizationEnabled()) { // TODO: Handle localized strings properly.
                    this->setDesc(QString::number(r.read<quint32>(), 16));
                    read += sizeof(quint32);
                } else {
                    this->setDesc(r.readZstring());
                    read += this->getDesc().length();
                }
                break;
            }
            // Spell count. SPLO records only present if this is. SPLO records follow directly after so we handle them here too.
            case 'SPCT': {

                quint32 spellCount{ 0 };
                spellCount = r.read<quint32>();
                read += sizeof(quint32);
                this->setSpellCount(spellCount);

                // Read SPLO records.
                read += this->readSpells(r, spellCount);

                break;
            }
            // Skin record
            case 'WNAM': {

                this->setSkin(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Body template BOD2 = 8 bytes. BODT = 12 bytes. BOD2 present in Skyrim SSE. BODT in LE.
            case 'BOD2': {
                r.read<quint32>();
                r.read<quint32>();
                //r.read<quint32>();
                read += sizeof(quint32) * 2;
                break;
            }
            case 'BODT': {
                r.read<quint32>();
                r.read<quint32>();
                r.read<quint32>();
                read += sizeof(quint32) * 3;
                break;
            }
            // Keyword size. Handle KWDA here too since they follow directly after.
            case 'KSIZ': {

                quint32 keywordCount{ 0 };
                keywordCount = r.read<quint32>();
                read += sizeof(quint32);
                this->setKeywordCount(keywordCount);

                // Read KWDA records.
                read += this->readKeywords(r, keywordCount);

                break;
            }
            default: {

                quint32 swappedType = r.swapType(h.type);
                char buf[5];
                memcpy(buf, &swappedType, sizeof(quint32));
                buf[4] = '\0';
                qDebug() << "Unhandled subrecord: " << buf;

                r.skip(header.getDataSize() - read);
                read = header.getDataSize();
                break;
            }
            //// DATA records. Total length = 128 for v40, 164 for v43.
            //case 'DATA': {

            //}
            }
        }
    }

    void RaceForm::addForm()
    {

    }

    void RaceForm::readForm()
    {

    }

    quint32 RaceForm::readSpells(io::Reader& r, quint32 length)
    {
        quint32 bytesRead = 0;
        for (quint32 i = 0; i < length; i++) {

            // Skip SPLO header.
            readSubrecord(r, &bytesRead);

            // Read form id.
            quint32 spellID{ 0 };
            spellID = r.read<quint32>();
            Spells.push_back(spellID);

            bytesRead += sizeof(quint32);
        }
        return bytesRead;
    }

    quint32 RaceForm::readKeywords(io::Reader& r, quint32 length)
    {
        quint32 bytesRead = 0;
        for (quint32 i = 0; i < length; i++) {

            // Skip KWDA header.
            readSubrecord(r, &bytesRead);

            // Read form id.
            quint32 keywordID{ 0 };
            keywordID = r.read<quint32>();
            Keywords.push_back(keywordID);

            bytesRead += sizeof(quint32);
        }
        return bytesRead;
    }
}