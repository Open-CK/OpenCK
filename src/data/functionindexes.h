/*
** functionindexes.h
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

#ifndef FUNCTIONINDEXES_H
#define FUNCTIONINDEXES_H

#include <QMap>
#include <QString>

namespace esx
{
    static QMap<quint32, QString> functionIndexes
    {
        { 0, "GameMode" },
        { 1, "MenuMode" },
        { 2, "OnActivate" },
        { 3, "OnAdd" },
        { 4, "OnEquip" },
        { 5, "OnUnequip" },
        { 6, "OnDrop" },
        { 7, "SayToDone" },
        { 8, "OnHit" },
        { 9, "OnHitWith" },
        { 10, "OnDeath" },
        { 11, "OnMurder" },
        { 12, "OnCombatEnd" },
        { 13, "Unused" },
        { 14, "Unused2" },
        { 15, "OnPackageStart" },
        { 16, "OnPackageDone" },
        { 17, "ScriptEffectStart" },
        { 18, "ScriptEffectFinish" },
        { 19, "ScriptEffectUpdate" },
        { 20, "OnPackageChange" },
        { 21, "OnLoad" },
        { 22, "OnMagicEffectHit" },
        { 23, "OnSell" },
        { 24, "OnTrigger" },
        { 25, "OnStartCombat" },
        { 26, "OnTriggerEnter" },
        { 27, "OnTriggerLeave" },
        { 28, "OnActorEquip" },
        { 29, "OnActorUnequip" },
        { 30, "OnReset" },
        { 31, "OnOpen" },
        { 32, "OnClose" },
        { 33, "OnGrab" },
        { 34, "OnRelease" },
        { 35, "OnDestructionStageChange" },

        //Console Commands
        { 256, "Show" },
        { 257, "ShowVars" },
        { 258, "ShowGlobalVars" },
        { 259, "ShowQuestVars" },
        { 260, "ShowQuests" },
        { 261, "ShowQuestAliases" },
        { 262, "SetPapyrusQuestVar" },
        { 263, "SetPapyrusVar" },
        { 264, "SetQuestAliases" },
        { 265, "ClearQuestAliases" },
        { 266, "ToggleCombatStats" },
        { 267, "ToggleSafeZone" },
        { 268, "ToggleAI" },
        { 269, "ToggleCollisionGeometry" },
        { 270, "ToggleMaterialGeometry" },
        { 271, "ToggleStairsGeometry" },
        { 272, "ToggleBorders" },
        { 273, "ToggleSky" },
        { 274, "ToggleWireframe" },
        { 275, "ToggleCollision" },
        { 276, "ToggleDebugText" },
        { 277, "ToggleMenus" },
        { 278, "TogglePrimitives" },
        { 279, "ShowSceneGraph" },
        { 280, "ShowFullSceneGraph" },
        { 281, "ToggleMagicStats" },
        { 282, "ShowAnims" },
        { 283, "Show1stPerson" }
    };
}

#endif // FUNCTIONINDEXES_H
