/*
** factionform.h
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
** Created Date: 19-Oct-2017
*/

#ifndef FACTIONFORM_H
#define FACTIONFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <vector>

#include <data/form.h>
#include <data/subrecords/interfactionrelationsfield.h>
#include <data/subrecords/conditionitemcountfield.h>

namespace esx
    {
    struct CrimeGold12Byte
    {
        quint8 arrest{ 0 };
        quint8 attack{ 0 };
        quint16 murder{ 0 };
        quint16 assault{ 0 };
        quint16 trespass{ 0 };
        quint16 pickpocket{ 0 };
        quint16 unused{ 0 };
    };

    struct CrimeGold
    {
        CrimeGold12Byte gold;
        float stealMult{ 0.0f };
        quint16 escape{ 0 };
        quint16 werewolf{ 0 };
    };

    struct Rank
    {
        quint32 rankID{ 0 };
        quint32 maleTitle{ 0 };
        quint32 femaleTitle{ 0 };
    };

    struct VendorInf
    {
        quint16 startHour{ 0 };
        quint16 endHour{ 0 };
        quint32 radius{ 0 };
        quint8 stolenFlag{ 0 };
        quint8 notSellFlag{ 0 };
        quint16 unused{ 0 };
    };

    struct VendorPlace
    {
        quint32 typeFlags{ 0 };
        quint32 form{ 0 };
        quint32 unused{ 0 };
    };

    typedef CrimeGold CrimeGold;
    typedef Rank Rank;
    typedef VendorInf VendorInf;
    typedef VendorPlace VendorPlace;

    class FactionForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(quint32, FullName)
        FORM_MEMBER(std::vector<InterfactionRelations>, Relations)
        FORM_MEMBER(quint32, Flags)
        FORM_MEMBER(quint32, PrisonMarker)
        FORM_MEMBER(quint32, FollowerWaitMarker)
        FORM_MEMBER(quint32, EvidenceChest)
        FORM_MEMBER(quint32, BelongingsChest)
        FORM_MEMBER(quint32, CrimeGroup)
        FORM_MEMBER(quint32, JailOutfit)
        FORM_MEMBER(CrimeGold, Gold)
        FORM_MEMBER(std::vector<Rank>, Ranks)
        FORM_MEMBER(quint32, VendorList)
        FORM_MEMBER(quint32, VendorChest)
        FORM_MEMBER(VendorInf, VendorData)
        FORM_MEMBER(VendorPlace, Place)
        FORM_MEMBER(ConditionItemCount, ConditionCount)


    public:
        FactionForm()
            : EditorID(""), FullName(0), Flags(0), PrisonMarker(0), FollowerWaitMarker(0), EvidenceChest(0), BelongingsChest(0),
            CrimeGroup(0), JailOutfit(0), VendorList(0), VendorChest(0) {}
        FactionForm(const Form&);
        ~FactionForm() = default;

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addFACT(FactionForm& form);
        void readFACT(FactionForm& form);
    };
}

#endif // FACTIONFORM_H
