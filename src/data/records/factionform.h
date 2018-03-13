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
        quint8 arrest;
        quint8 attack;
        quint16 murder;
        quint16 assault;
        quint16 trespass;
        quint16 pickpocket;
        quint16 unused;
    };

    struct CrimeGold16Byte
    {
        CrimeGold12Byte gold;
        float stealMult;
    };

    struct CrimeGold20Byte
    {
        CrimeGold12Byte gold;
        float stealMult;
        quint16 escape;
        quint16 werewolf;
    };

    struct Rank
    {
        quint32 rankID;
        quint32 maleTitle;
        quint32 femaleTitle;
    };

    struct VendorInf
    {
        quint16 startHour;
        quint16 endHour;
        quint32 radius;
        quint8 stolenFlag;
        quint8 notSellFlag;
        quint16 unused;
    };

    struct VendorPlace
    {
        quint32 typeFlags;
        quint32 form;
        quint32 unused;
    };

    typedef CrimeGold12Byte CrimeGold12Byte;
    typedef CrimeGold16Byte CrimeGold16Byte;
    typedef CrimeGold20Byte CrimeGold20Byte;
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
        FORM_MEMBER(CrimeGold12Byte, Gold12)
        FORM_MEMBER(CrimeGold16Byte, Gold16)
        FORM_MEMBER(CrimeGold20Byte, Gold20)
        FORM_MEMBER(std::vector<Rank>, Ranks)
        FORM_MEMBER(quint32, VendorList)
        FORM_MEMBER(quint32, VendorChest)
        FORM_MEMBER(VendorInf, VendorData)
        FORM_MEMBER(VendorPlace, Place)
        FORM_MEMBER(ConditionItemCount, ConditionCount)


    public:
        FactionForm();
    };
}

#endif // FACTIONFORM_H
