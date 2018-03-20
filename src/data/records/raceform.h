/*
** raceform.h
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

#ifndef RACEFORM_H
#define RACEFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <vector>
#include <array>
#include <data/form.h>
#include <data/subrecords/bodytemplatefield.h>

namespace esx
{
    struct RaceData
    {
        std::array<quint8, 7> skills{ 0 };
        std::array<quint8, 7> racialBonus{ 0 };

        quint16 padding{ 0 };

        float maleHeight{ 0.0f };
        float femaleHeight{ 0.0f };

        float maleWeight{ 0.0f };
        float femaleWeight{ 0.0f };

        quint32 flags{ 0 };

        float startingHealth{ 0.0f };
        float startingMagicka{ 0.0f };
        float startingStamina{ 0.0f };

        float baseCarryWeight{ 0.0f };
        
        float baseMass{ 0.0f };
        float accelRate{ 0.0f };
        float decelRate{ 0.0f };

        quint32 size{ 0 };

        quint32 headBiped{ 0 };
        quint32 hairBiped{ 0 };

        float injuredHealthPercentage{ 0.0f };
        quint32 shieldBiped{ 0 };

        float healthRegen{ 0.0f };
        float magickaRegen{ 0.0f };
        float staminaRegen{ 0.0f };
        float unarmedDamage{ 0.0f };
        float unarmedReach{ 0.0f };

        quint32 bodyBiped{ 0 };

        float aimAngleTolerence{ 0.0f };
        quint32 unk0{ 0 };
        float angularAccelRate{ 0.0f };
        float angularTolerance{ 0.0f };

        quint32 flags2{ 0 };

        std::array<float, 9> mountData{ 0.0f };
    };

    struct RaceAttackData
    {
        float damageMultiplier{ 0.0f };
        float attackChance{ 0.0f };
        quint32 attackSpell{ 0 };
        quint32 flags{ 0 };
        float attackAngle{ 0.0f };
        float strikeAngle{ 0.0f };
        float stagger{ 0.0f };
        quint32 attackType{ 0 };
        float knockdown{ 0.0f };
        float recoveryTime{ 0.0f };
        float fatigueMulitplier{ 0.0f };
    };

    class RaceForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(QString, FullName)
        FORM_MEMBER(QString, Desc)
        FORM_MEMBER(quint32, SpellCount)
        FORM_MEMBER(std::vector<quint32>, Spells)
        FORM_MEMBER(quint32, Skin)
        FORM_MEMBER(BodyTemplateField, BodyTemplate)
        FORM_MEMBER(quint32, KeywordCount)
        FORM_MEMBER(std::vector<quint32>, Keywords)
        FORM_MEMBER(RaceData, Data)

        FORM_MEMBER(QString, MaleSkeletalModel)
        FORM_MEMBER(QString, FemaleSkeletalModel)

        FORM_MEMBER(std::vector<quint32>, MovementTypes)

        FORM_MEMBER(quint32, MaleVoiceType)
        FORM_MEMBER(quint32, FemaleVoiceType)

        FORM_MEMBER(quint32, MaleDecapArmor)
        FORM_MEMBER(quint32, FemaleDecapArmor)

        FORM_MEMBER(quint32, MaleDefaultHairColor)
        FORM_MEMBER(quint32, FemaleDefaultHairColor)

        FORM_MEMBER(quint16, TintIndexTotal)
        FORM_MEMBER(float, FaceGenMainClamp)
        FORM_MEMBER(float, FaceGenFaceClamp)

        FORM_MEMBER(quint32, AttackRace)
        FORM_MEMBER(std::vector<RaceAttackData>, AttackData)
        FORM_MEMBER(std::vector<QString>, AttackEvent)
    public:
        RaceForm() {}
        RaceForm(const Form& form);
        ~RaceForm() = default;

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addRACE(RaceForm& RACE);
        void readRACE(RaceForm& RACE);

    private:
        quint32 readSpells(io::Reader& r, quint32 length);
        quint32 readKeywords(io::Reader& r, quint32 length);
    };
}

#endif