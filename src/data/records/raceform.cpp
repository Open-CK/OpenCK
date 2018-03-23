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
#include <io/parser.h>

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
        quint32 read{ 0 };
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

                read += this->readData(r);
                
                break;
            }
            // Male marker.
            case 'MNAM': {

                read += this->readModelInfo(r, &MaleModelInfo);

                break;
            }
            // Female marker.
            case 'FNAM': {

                read += this->readModelInfo(r, &FemaleModelInfo);

                break;
            }
            // Movement type name
            case 'MTNM': {

                QString mtype;
                mtype = r.readZstring();

                MovementTypeNames.push_back(mtype);

                read += mtype.size();

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

                read += this->readEGT(r);

                break;
            }
            // Havok model
            case 'NAM3': {

                read += this->readHavok(r);

                break;
            }
            // Body part data
            case 'GNAM': {

                setBodyPartData(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // MATT formid
            case 'NAM4': {

                this->setMaterialType(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Impact data set
            case 'NAM5': {

                this->setImpactDataSet(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Decap FX
            case 'NAM7': {

                this->setDecapFX(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Open loot sound
            case 'ONAM': {

                this->setOpenLootSound(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Close loot sound
            case 'LNAM': {

                this->setCloseLootSound(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Biped object names. Should be 32.
            case 'NAME': {

                QString bipedName = r.readZstring();
                BipedObjectNames.push_back(bipedName);
                read += bipedName.size();

                break;
            }
            // Movement override formid
            case 'MTYP': {

                MovementType mtype;
                mtype.type = r.read<quint32>();
                MovementTypes.push_back(mtype);
                lastMovementType = &MovementTypes.back();
                read += sizeof(quint32);

                break;
            }
            // Speed data values
            case 'SPED': {

                SPEDData spd;
                for (quint32 i = 0; i < spd.unk.size(); i++) {
                    spd.unk[i] = r.read<float>();
                    read += sizeof(float);
                }
                //SpeedData.push_back(spd);
                if (lastMovementType) {
                    lastMovementType->hasSpeedData = true;
                    lastMovementType->speedData = spd;
                }

                break;
            }
            // Equipment type flags.
            case 'VNAM': {

                this->setEquipmentTypeFlags(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Equip slots
            case 'QNAM': {

                quint32 slot = r.read<quint32>();
                EquipSlots.push_back(slot);
                read += sizeof(quint32);

                break;
            }
            // Unarmed equip slot
            case 'UNES': {

                this->setUnarmedEquipSlot(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Facial keys
            case 'PHTN': {

                QString key;
                key = r.readZstring();
                read += key.size();
                FacialKeys.push_back(key);

                break;
            }
            // Facial weight
            case 'PHWT': {

                PHWTData data;
                quint32 weightsTotal = h.size / sizeof(float);
                data.weights.resize(weightsTotal, 0.0f);
                for (quint32 i = 0; i < weightsTotal; i++) {
                    data.weights[i] = r.read<float>();
                    read += sizeof(float);
                }
                FacialWeights.push_back(data);

                break;
            }
            // Walk MOVT record
            case 'WKMV': {
                
                this->setWalkMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Run MOVT record
            case 'RNMV': {

                this->setRunMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Swim MOVT record
            case 'SWMV': {

                this->setSwimMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Fly MOVT record
            case 'FLMV': {

                this->setFlyMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Sneak MOVT record
            case 'SNMV': {

                this->setSneakMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Sprint MOVT record
            case 'SPMV': {

                this->setSprintMove(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Head info
            case 'NAM0': {

                HeadData* data{ nullptr };
                auto marker = readSubrecord(r, &read);
                if (marker.type == 'MNAM') {
                    data = &MaleHeadData;
                } else {
                    data = &FemaleHeadData;
                }

                read += this->readHeadInfo(r, data);

                break;
            }
            // Morph Race
            case 'NAM8': {

                this->setMorphRace(r.read<quint32>());
                read += sizeof(quint32);

                break;
            }
            // Armor Race
            case 'RNAM': {

                this->setArmorRace(r.read<quint32>());
                read += sizeof(quint32);

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
        connect(this, &RaceForm::addRACE,
            &io::Parser::getParser().getFileModel(), &models::FileModel::insertRACE);
        emit addRACE(*this);
    }

    void RaceForm::readForm()
    {
        connect(this, &RaceForm::readRACE,
            &io::Parser::getParser().getFormModel(), &models::FormModel::readRACE);
        emit readRACE(*this);
    }

    quint32 RaceForm::readSpells(io::Reader& r, quint32 length)
    {
        quint32 bytesRead{ 0 };
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
        quint32 bytesRead{ 0 };
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

    quint32 RaceForm::readData(io::Reader& r)
    {
        quint32 read{ 0 };
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

        return read;
    }

    quint32 RaceForm::readModelInfo(io::Reader& r, ModelInfo* info)
    {
        quint32 read{ 0 };
        auto nextRecord = peekSubrecord(r);

        if (nextRecord.type == 'ANAM') {

            readSubrecord(r, &read);

            info->model = r.readZstring();
            read += info->model.size();

            nextRecord = peekSubrecord(r);
        }

        // This is supposedly variable... Only found 12 bytes in RACE so far or no record at all.
        if (nextRecord.type == 'MODT') {
            readSubrecord(r, &read);

            for (quint32 i = 0; i < 12; i++) {
                info->modt[i] = r.read<quint8>();
                read += sizeof(quint8);
            }
        }

        return read;
    }

    quint32 RaceForm::readEGT(io::Reader& r)
    {
        // Total bytes read.
        quint32 read{ 0 };

        // MNAM marker
        auto nextRecord = readSubrecord(r, &read);

        EgtModel maleModel;

        // INDX marker.
        nextRecord = readSubrecord(r, &read);
        maleModel.index = r.read<quint32>();
        read += sizeof(quint32);

        // Peek male model data.
        nextRecord = peekSubrecord(r);

        // Lighting model.
        if (nextRecord.type == 'MODL') {
            readSubrecord(r, &read);

            maleModel.model = r.readZstring();
            read += maleModel.model.size();


            nextRecord = peekSubrecord(r);
        }

        if (nextRecord.type == 'MODT') {
            readSubrecord(r, &read);

            for (quint32 i = 0; i < maleModel.modt.size(); i++) {
                maleModel.modt[i] = r.read<quint8>();
                read += sizeof(quint8);
            }
        }
        this->setMaleEgtModel(maleModel);

        // Female record. FNAM
        nextRecord = readSubrecord(r, &read);

        // INDX record
        EgtModel femaleModel;
        nextRecord = readSubrecord(r, &read);
        femaleModel.index = r.read<quint32>();
        read += sizeof(quint32);

        // Peek female model data.
        nextRecord = peekSubrecord(r);

        if (nextRecord.type == 'MODL') {
            readSubrecord(r, &read);

            femaleModel.model = r.readZstring();
            read += femaleModel.model.size();

            nextRecord = peekSubrecord(r);
        }

        if (nextRecord.type == 'MODT') {
            readSubrecord(r, &read);

            for (quint32 i = 0; i < femaleModel.modt.size(); i++) {
                femaleModel.modt[i] = r.read<quint8>();
                read += sizeof(quint8);
            }
        }
        this->setFemaleEgtModel(femaleModel);

        return read;
    }

    quint32 RaceForm::readHavok(io::Reader& r)
    {
        quint32 read{ 0 };
        
        // MNAM marker
        HavokModel maleModel;
        auto nextSubrecord = readSubrecord(r, &read);

        nextSubrecord = peekSubrecord(r);

        if (nextSubrecord.type == 'MODL') {
            readSubrecord(r, &read);

            maleModel.model = r.readZstring();
            read += maleModel.model.size();

            nextSubrecord = peekSubrecord(r);
        }

        if (nextSubrecord.type == 'MODT') {
            readSubrecord(r, &read);

            for (quint32 i = 0; i < maleModel.modt.size(); i++) {
                maleModel.modt[i] = r.read<quint8>();
                read += sizeof(quint8);
            }
        }
        this->setMaleHavokModel(maleModel);

        // FNAM marker
        HavokModel femaleModel;
        nextSubrecord = readSubrecord(r, &read);

        nextSubrecord = peekSubrecord(r);

        if (nextSubrecord.type == 'MODL') {
            readSubrecord(r, &read);

            femaleModel.model = r.readZstring();
            read += femaleModel.model.size();

            nextSubrecord = peekSubrecord(r);
        }

        if (nextSubrecord.type == 'MODT') {
            readSubrecord(r, &read);
            for (quint32 i = 0; i < femaleModel.modt.size(); i++) {
                femaleModel.modt[i] = r.read<quint8>();
                read += sizeof(quint8);
            }
        }
        this->setFemaleHavokModel(femaleModel);

        return read;
    }

    quint32 RaceForm::readHeadInfo(io::Reader& r, HeadData* headData)
    {
        quint32 read{ 0 };

        // Read head parts.
        auto nextSubrecord = peekSubrecord(r);

        while (nextSubrecord.type == 'INDX') {
            readSubrecord(r, &read);

            HeadPart head;
            // Read index
            head.index = r.read<quint32>();
            read += sizeof(quint32);

            // Read HEAD
            readSubrecord(r, &read);
            head.data = r.read<quint32>();
            read += sizeof(quint32);

            headData->headParts.push_back(head);

            // Grab the next record.
            nextSubrecord = peekSubrecord(r);
        }

        // Read morphs.
        while (nextSubrecord.type == 'MPAI') {
            readSubrecord(r, &read);

            HeadMorphData morphData;
            // Read index
            morphData.index = r.read<quint32>();
            read += sizeof(quint32);

            // Read data
            readSubrecord(r, &read);
            morphData.data.flags = r.read<quint32>();
            read += sizeof(quint32);

            for (quint32 i = 0; i < morphData.data.unk.size(); i++) {
                morphData.data.unk[i] = r.read<quint32>();
                read += sizeof(quint32);
            }

            headData->morphs.push_back(morphData);

            // Grab the next record.
            nextSubrecord = peekSubrecord(r);
        }

        // Race presets.
        while (((nextSubrecord.type & 0xFFFFFF00) >> 8) == 'RPR') {
            readSubrecord(r, &read);

            quint32 preset = r.read<quint32>();
            headData->presets.push_back(preset);
            read += sizeof(quint32);

            nextSubrecord = peekSubrecord(r);
        }

        // Hair colors.
        while (((nextSubrecord.type & 0xFFFFFF00) >> 8) == 'AHC') {
            readSubrecord(r, &read);

            quint32 hairColor = r.read<quint32>();
            headData->hairColors.push_back(hairColor);
            read += sizeof(quint32);

            nextSubrecord = peekSubrecord(r);
        }

        // Face details texture set list
        while (((nextSubrecord.type & 0xFFFFFF00) >> 8) == 'FTS') {
            readSubrecord(r, &read);

            quint32 faceTextureSet = r.read<quint32>();
            headData->textureSetLists.push_back(faceTextureSet);
            read += sizeof(quint32);

            nextSubrecord = peekSubrecord(r);
        }

        // Default face texture
        if (((nextSubrecord.type & 0xFFFFFF00) >> 8) == 'DFT') {
            readSubrecord(r, &read);

            headData->defaultFaceTexture = r.read<quint32>();
            read += sizeof(quint32);

            nextSubrecord = peekSubrecord(r);
        }

        // Tint masks.
        while(nextSubrecord.type == 'TINI') {
            readSubrecord(r, &read);

            HeadTint tint;
            read += readTint(r, &tint);
            headData->tints.push_back(tint);

            nextSubrecord = peekSubrecord(r);
        }

        return read;
    }

    quint32 RaceForm::readTint(io::Reader& r, HeadTint* tint)
    {
        quint32 read{ 0 };

        // Read index.
        tint->index = r.read<quint16>();
        read += sizeof(quint16);

        auto nextSubrecord = peekSubrecord(r);

        // Read mask if exists.
        if (nextSubrecord.type == 'TINT') {
            readSubrecord(r, &read);

            tint->mask = r.readZstring();
            read += tint->mask.size();

            nextSubrecord = peekSubrecord(r);
        }

        // Read mask type if exists.
        if (nextSubrecord.type == 'TINP') {
            readSubrecord(r, &read);
            
            tint->maskType = r.read<quint16>();
            read += sizeof(quint16);

            nextSubrecord = peekSubrecord(r);
        }

        // Read preset default if exists.
        if (nextSubrecord.type == 'TIND') {
            readSubrecord(r, &read);

            tint->presetDefault = r.read<quint32>();
            read += sizeof(quint32);

            nextSubrecord = peekSubrecord(r);
        }

        // Read presets.
        while (nextSubrecord.type == 'TINC') {
            readSubrecord(r, &read);

            HeadTintPreset p;
            // Preset formid
            p.preset = r.read<quint32>();
            read += sizeof(quint32);

            // default value
            readSubrecord(r, &read);
            p.defaultValue = r.read<float>();
            read += sizeof(float);

            // tint #
            readSubrecord(r, &read);
            p.tintNumber = r.read<quint16>();
            read += sizeof(quint16);

            tint->presets.push_back(p);

            nextSubrecord = peekSubrecord(r);
        }

        return read;
    }
}