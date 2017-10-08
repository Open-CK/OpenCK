/*
** tes4record.h
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
** Created Date: 10-Jul-2017
*/

//!@file tes4form.h Header for the TES4 record class.

#ifndef TES4FORM_H
#define TES4FORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <QString>
#include <QMap>
#include <QVector>

#include "form.h"

namespace esx
{
    //Enable use of type in macro
    typedef QMap<QString, quint64> MastersMap;

    /**
     * The class for the TES4 header in .esp and .esm files.
     * @brief The class for the TES4 header.
     */
    class TES4Form : public Form
    {
        Q_OBJECT

        FORM_MEMBER(float, Version)
        FORM_MEMBER(qint32, NumRecords)
        FORM_MEMBER(quint32, NextID)
        FORM_MEMBER(QString, Author)
        FORM_MEMBER(QString, Desc)
        FORM_MEMBER(MastersMap, Masters)
        FORM_MEMBER(QVector<quint32>, Overrides)
        FORM_MEMBER(quint32, Intv)
        FORM_MEMBER(quint32, Incc)

    public:
        TES4Form() {}
        TES4Form(const Form &formHeader);
        ~TES4Form();

        void load(QDataStream* in, const int fileNumber) override;
        void addForm(const int fileNumber);

    signals:
        void addTES4(TES4Form& form, const int fileNumber);
    };
}
#endif // TES4FORM_H
