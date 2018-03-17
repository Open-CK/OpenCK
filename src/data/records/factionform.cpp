/*
** factionform.cpp
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

#include <data/records/factionform.h>
#include <io/parser.h>

#include <iostream>
#include <assert.h>

namespace esx
{
    /**
    * Create a new form by copying an existing header.
    * @brief Create a new form from header.
    * @param f Form header read by parser.
    */
    FactionForm::FactionForm(const Form &f)
        : FactionForm()
    {
        this->header = f.getHeader();
        this->header.setName(FormName::Faction);
    }

    /**
    * Loads the FACT header from the data stream.
    * @brief Loads the header.
    * @param r Reader object that performs all parsing functions.
    */
    void FactionForm::load(io::Reader& r)
    {
        static QSet<quint32> subrecords = {
            'EDID',
            'FULL',
            'XNAM',
            'DATA',
            'JAIL',
            'WAIT',
            'STOL',
            'PLCN',
            'CRGR',
            'JOUT',
            'CRVA',
            'RNAM',
            'MNAM',
            'FNAM',
            'VEND',
            'VENC',
            'VENV',
            'PLVD',
            'CITC',
            'CTDA'
        };

        quint32 read = 0;
        while (read < header.getDataSize()) {
            SubrecordHeader h = readSubrecord(r, &read);

            switch (h.type) {
                case 'EDID': // Editor ID
                    this->setEditorID(r.readZstring());
                    read += this->getEditorID().length();
                    break;
                case 'FULL': // Full name
                    this->setFullName(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'XNAM': // Interfaction relations.
                    Relations.push_back({ r.read<quint32>(), r.read<qint32>(), r.read<qint32>() });
                    read += sizeof(quint32) * 3;
                    break;
                case 'DATA': // Flags
                    this->setFlags(r.read<qint32>());
                    read += sizeof(qint32);
                    break;
                case 'JAIL': // Prison Marker.
                    this->setPrisonMarker(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'WAIT': // Follow wait marker.
                    this->setFollowerWaitMarker(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'STOL': // Evidence Chest
                    this->setEvidenceChest(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'PLCN': // Player Belongings Chest
                    this->setBelongingsChest(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'CRGR': // Crime Group
                    this->setCrimeGroup(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                case 'JOUT': // Jail Outfit
                    this->setJailOutfit(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                // Crime values
                case 'CRVA': {
                    // These fields should exist in all form versions.
                    esx::CrimeGold cg;
                    cg.gold.arrest = r.read<quint8>();
                    cg.gold.attack = r.read<quint8>();
                    cg.gold.murder = r.read<quint16>();
                    cg.gold.assault = r.read<quint16>();
                    cg.gold.trespass = r.read<quint16>();
                    cg.gold.pickpocket = r.read<quint16>();
                    cg.gold.unused = r.read<quint16>();
                    read += sizeof(esx::CrimeGold12Byte);

                    // Find optional fields depending on version number.
                    auto headerVersion = header.getVersion();

                    if (headerVersion > 30) {
                        cg.stealMult = r.read<quint32>();
                        cg.escape = r.read<quint16>();
                        cg.werewolf = r.read<quint16>();
                        read += 8;

                    } else {
                        // Peek to next subsection or end
                        qint64 origin = r.pos();
                        qint64 peekRead = origin;
                        bool found = false;
                        while (peekRead < (origin + (header.getDataSize() - read))) {

                            // Peek the data and byteswap the result.
                            quint32 sub = r.peek<quint32>();
                            sub = (sub >> 24 |
                                  ((sub << 8) & 0x00FF0000) |
                                  ((sub >> 8) & 0x0000FF00) |
                                  sub << 24);

                            // Check if data fits one of our subheaders.
                            found = subrecords.contains(sub);
                            if (found)
                                break;

                            // Seek further when not found.
                            peekRead += sizeof(quint8);
                            r.seek(peekRead);
                        };

                        // Seek cursor back to origin.
                        r.seek(origin);

                        // Calculate offset from origin to peek end.
                        quint32 peekOffset = peekRead - origin;
                        if (peekOffset == 8) {
                            cg.stealMult = r.read<quint32>();
                            cg.escape = r.read<quint16>();
                            cg.werewolf = r.read<quint16>();
                            read += 8;
                        } else if (peekOffset == 4) {
                            cg.stealMult = r.read<quint32>();
                            read += 4;
                        }
                    }

                    this->setGold(cg);
                    break;
                }
                // Rank Name
                case 'RNAM': {
                    Ranks.push_back({ r.read<Rank>() });
                    read += sizeof(quint32);
                    break;
                }
                // Male Rank Title
                case 'MNAM':
                    Ranks.back().maleTitle = r.read<quint32>();
                    read += sizeof(quint32);
                    break;
                // Female Rank Title
                case 'FNAM':
                    Ranks.back().femaleTitle = r.read<quint32>();
                    read += sizeof(quint32);
                    break;
                 // Vendor List
                case 'VEND':
                    this->setVendorList(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                // Vendor Chest
                case 'VENC':
                    this->setVendorChest(r.read<quint32>());
                    read += sizeof(quint32);
                    break;
                 // Vendor
                case 'VENV': {
                    VendorInf inf;
                    inf.startHour = r.read<quint16>();
                    inf.endHour = r.read<quint16>();
                    inf.radius = r.read<quint32>();
                    inf.stolenFlag = r.read<quint8>();
                    inf.notSellFlag = r.read<quint8>();
                    inf.unused = r.read<quint16>();

                    this->setVendorData(inf);

                    read += sizeof(VendorInf);
                    break;
                }
                // Sell Place
                case 'PLVD': {
                    VendorPlace place;

                    place.typeFlags = r.read<quint32>();
                    place.form = r.read<quint32>();
                    place.unused = r.read<quint32>();

                    this->setPlace(place);
                    read += sizeof(VendorPlace);
                    break;
                }
                case 'CITC': // Condition field count.
                    this->setConditionCount({ r.read<quint32>() });
                    read += sizeof(quint32);
                    break;
                // TODO: Implement conditions. Skips for now.
                case 'CTDA': {
                    qint64 readOffset = r.pos() + (header.getDataSize() - read);
                    r.seek(readOffset);
                    read = header.getDataSize();
                    break;
                }
            }
        }
    }

    /**
    * Signal. Add the form to the file model.
    * @brief Add form to file model.
    */
    void FactionForm::addForm()
    {
        connect(this, &FactionForm::addFACT,
            &io::Parser::getParser().getFileModel(), &models::FileModel::insertFACT);
        emit addFACT(*this);
    }

    /**
    * Signal. Display the contents of a form stored in the file model to the form model.
    * @brief Display contents in form model.
    */
    void FactionForm::readForm()
    {
        connect(this, &FactionForm::readFACT,
            &io::Parser::getParser().getFormModel(), &models::FormModel::readFACT);
        emit readFACT(*this);
    }
}
