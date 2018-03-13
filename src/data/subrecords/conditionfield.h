/*
** conditionitemcountfield.h
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
** Created Date: 13-Mar-2018
*/

#ifndef CONDITIONITEMCOUNTFIELD_H
#define CONDITIONITEMCOUNTFIELD_H

namespace esx
{
    struct Params1
    {
        qint32 param1;
        qint32 param2;
    };

    struct Params2
    {
        quint16 param1;
        quint8 param2;
        qint32 param3;
    };

    struct Ops
    {
        quint32 application;
        qint32 referenceForm;
        qint32 unknown;
    };

    struct Condition
    {
        quint8 op;
        quint8 unknown[3];
        quint comparisonValue;
        quint16 index;
        quint8 padding[2];

        Params1 params1;
        Params2 params2;
        Ops ops;
    };

    typedef Condition Condition;
    typedef Params1 Params1;
    typedef Params2 Params2;
    typedef Ops Ops;
}

#endif // CONDITIONITEMCOUNTFIELD_H
