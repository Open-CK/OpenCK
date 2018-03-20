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
        : RaceForm()
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

                BodyTemplateField bodyTemplate;
                bodyTemplate.version = BodyTemplateField::BOD2;
                bodyTemplate.bodyPartFlags = r.read<quint32>();
                bodyTemplate.skill = r.read<quint32>();

                this->setBodyTemplate(bodyTemplate);

                read += sizeof(quint32) * 2;
                break;
            }
            case 'BODT': {

                BodyTemplateField bodyTemplate;
                bodyTemplate.version = BodyTemplateField::BODT;
                bodyTemplate.bodyPartFlags = r.read<quint32>();
                bodyTemplate.flags.data = r.read<quint32>();
                bodyTemplate.skill = r.read<quint32>();

                this->setBodyTemplate(bodyTemplate);

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
            // DATA record. Total length = 128 for v40, 164 for v43 (Mount data).
            case 'DATA': {

                RaceData data;

                // Read skills and racials in pairs.
                for (quint32 i = 0; i < data.skills.size(); i++) {
                    data.skills[i] = r.read<quint8>();
                    data.racialBonus[i] = r.read<quint8>();

                    read += sizeof(quint8) * 2;
                }

                // Read padding.
                data.padding = r.read<quint16>();
                read += sizeof(quint16);

                // Height and Weight.
                data.maleHeight = r.read<float>();
                data.femaleHeight = r.read<float>();
                data.maleWeight = r.read<float>();
                data.femaleWeight = r.read<float>();
                read += sizeof(float) * 4;

                // Flags
                data.flags = r.read<quint32>();
                read += sizeof(quint32);

                // Starting stats.
                data.startingHealth = r.read<float>();
                data.startingMagicka = r.read<float>();
                data.startingStamina = r.read<float>();
                data.baseCarryWeight = r.read<float>();
                read += sizeof(float) * 4;

                // Physics
                data.baseMass = r.read<float>();
                data.accelRate = r.read<float>();
                data.decelRate = r.read<float>();
                read += sizeof(float) * 3;

                // Biped
                data.size = r.read<quint32>();
                data.headBiped = r.read<quint32>();
                data.hairBiped = r.read<quint32>();
                data.injuredHealthPercentage = r.read<float>();
                data.shieldBiped = r.read<quint32>();
                read += (sizeof(quint32) * 4) + sizeof(float);

                // Regen values.
                data.healthRegen = r.read<float>();
                data.magickaRegen = r.read<float>();
                data.staminaRegen = r.read<float>();
                read += sizeof(float) * 3;

                // Unarmed values
                data.unarmedDamage = r.read<float>();
                data.unarmedReach = r.read<float>();
                read += sizeof(float) * 2;

                // Body biped
                data.bodyBiped = r.read<quint32>();
                read += sizeof(quint32);

                // Aim angle.
                data.aimAngleTolerence = r.read<float>();
                data.unk0 = r.read<quint32>();
                data.angularAccelRate = r.read<float>();
                data.angularTolerance = r.read<float>();
                read += sizeof(quint32) + (sizeof(float) * 3);

                // Flags 2
                data.flags2 = r.read<quint32>();
                read += sizeof(quint32);

                // Mount data (Only present in ver 43 upward).
                if (this->getHeader().getVersion() >= 43)
                {
                    for (quint32 i = 0; i < data.mountData.size(); i++) {
                        data.mountData[i] = r.read<float>();
                        read += sizeof(float);
                    }
                }

                this->setData(data);
                break;
            }
            // Male marker.
            case 'MNAM': {

                auto nextRecord = peekSubrecord(r);

                if (nextRecord.type == 'ANAM') {

                    readSubrecord(r, &read);

                    this->setMaleSkeletalModel(r.readZstring());
                    read += this->getMaleSkeletalModel().size();
                    
                    nextRecord = peekSubrecord(r);
                }

                if (nextRecord.type == 'MODT') {
                    readSubrecord(r, &read);

                    struct unk
                    {
                        quint32 d[3];
                    };

                    r.read<unk>();

                    read += sizeof(quint32) * 3;
                }

                break;
            }
            // Female marker.
            case 'FNAM': {

                auto nextRecord = peekSubrecord(r);

                if (nextRecord.type == 'ANAM') {

                    readSubrecord(r, &read);

                    this->setFemaleSkeletalModel(r.readZstring());
                    read += this->getFemaleSkeletalModel().size();

                    nextRecord = peekSubrecord(r);
                }

                if (nextRecord.type == 'MODT') {
                    readSubrecord(r, &read);

                    struct unk
                    {
                        quint32 d[3];
                    };

                    r.read<unk>();

                    read += sizeof(quint32) * 3;
                }

                break;
            }
            // Movement type name
            case 'MTNM': {

                quint32 mtype{ 0 };
                mtype = r.read<quint32>();

                MovementTypes.push_back(mtype);

                read += sizeof(quint32);

                break;
            }
            // Default voice types
            case 'VTCK': {

                this->setMaleVoiceType(r.read<quint32>());
                this->setFemaleVoiceType(r.read<quint32>());
                read += sizeof(quint32) * 2;

                break;
            }
            // Decapitation armor
            case 'DNAM': {

                this->setMaleDecapArmor(r.read<quint32>());
                this->setFemaleDecapArmor(r.read<quint32>());
                read += sizeof(quint32) * 2;

                break;
            }
            // Default hair color
            case 'HCLF': {

                this->setMaleDefaultHairColor(r.read<quint32>());
                this->setFemaleDefaultHairColor(r.read<quint32>());
                read += sizeof(quint32) * 2;

                break;
            }
            // Tint index total
            case 'TINL': {
                this->setTintIndexTotal(r.read<quint16>());
                read += sizeof(quint16);
                break;
            }
            // FaceGen - Main clamp
            case 'PNAM': {
                this->setFaceGenMainClamp(r.read<float>());
                read += sizeof(float);
                break;
            }
            // FaceGen - Face clamp
            case 'UNAM': {
                this->setFaceGenFaceClamp(r.read<float>());
                read += sizeof(float);
                break;
            }
            // Attack race
            case 'ATKR': {
                this->setAttackRace(r.read<quint32>());
                read += sizeof(quint32);
                break;
            }
            // Attack data
            case 'ATKD': {

                RaceAttackData data;
                data.damageMultiplier = r.read<float>();
                data.attackChance = r.read<float>();
                data.attackSpell = r.read<quint32>();
                data.flags = r.read<quint32>();
                data.attackAngle = r.read<float>();
                data.strikeAngle = r.read<float>();
                data.stagger = r.read<float>();
                data.attackType = r.read<quint32>();
                data.knockdown = r.read<float>();
                data.recoveryTime = r.read<float>();
                data.fatigueMulitplier = r.read<float>();

                AttackData.push_back(data);
                read += (sizeof(float) * 8) + (sizeof(quint32) * 3);

                break;
            }
            // Attack event (Pairs to last ATKD encountered).
            case 'ATKE': {

                QString ev;
                ev = r.readZstring();
                AttackEvent.push_back(ev);
                read += ev.size();

                break;
            }
            // NAM1 - egt models
            case 'NAM1': {

                // MNAM marker
                auto nextRecord = readSubrecord(r, &read);
                
                // INDX marker.
                nextRecord = readSubrecord(r, &read);
                quint32 indx = r.read<quint32>();
                read += sizeof(quint32);

                // Peek male model data.
                nextRecord = peekSubrecord(r);

                // Lighting model.
                if (nextRecord.type == 'MODL') {
                    readSubrecord(r, &read);

                    this->setMaleLightingModel(r.readZstring());
                    read += this->getMaleLightingModel().size();

                    nextRecord = peekSubrecord(r);
                }

                struct unk
                {
                    quint32 data[3];
                };

                if (nextRecord.type == 'MODT') {
                    readSubrecord(r, &read);

                    r.read<unk>();
                    read += sizeof(unk);

                }

                // Female record. FNAM
                nextRecord = readSubrecord(r, &read);

                // INDX record
                nextRecord = readSubrecord(r, &read);
                indx = r.read<quint32>();
                read += sizeof(quint32);

                // Peek female model data.
                nextRecord = peekSubrecord(r);

                if (nextRecord.type == 'MODL') {
                    readSubrecord(r, &read);

                    this->setFemaleLightingModel(r.readZstring());
                    read += this->getFemaleLightingModel().size();

                    nextRecord = peekSubrecord(r);
                }

                if (nextRecord.type == 'MODT') {
                    readSubrecord(r, &read);

                    r.read<unk>();
                    read += sizeof(unk);

                }

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
        // Skip KWDA header.
        readSubrecord(r, &bytesRead);

        for (quint32 i = 0; i < length; i++) {

            // Read form id.
            quint32 keywordID{ 0 };
            keywordID = r.read<quint32>();
            Keywords.push_back(keywordID);

            bytesRead += sizeof(quint32);
        }
        return bytesRead;
    }
}