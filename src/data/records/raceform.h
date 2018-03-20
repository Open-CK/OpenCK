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
#include <data/form.h>

namespace esx
{
    struct RaceBodyTemplate
    {
        quint32 bipedFlags;
        quint32 generalFlags;
        quint32 armorType;
    };

    struct RaceData
    {
        std::array<quint8, 7> skills;
        std::array<quint8, 7> racialBonus;

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

        float aimAngleTolerence{ 0.0f };
        quint32 unk0{ 0 };
        float angularAccelRate{ 0.0f };
        float angularTolerance{ 0.0f };

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
        FORM_MEMBER(RaceBodyTemplate, BodyTemplate)
        FORM_MEMBER(quint32, KeywordCount)
        FORM_MEMBER(std::vector<quint32>, Keywords)
        FORM_MEMBER(RaceData, Data)

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