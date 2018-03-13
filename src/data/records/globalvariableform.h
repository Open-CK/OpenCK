/*
** globalvariableform.h
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
** Created Date: 16-Oct-2017
*/

//!@file form.h Header for the Global Variable form class.

#ifndef GLOBALVARIABLEFORM_H
#define GLOBALVARIABLEFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <data/form.h>

namespace esx
{
    /**
     * The Global Variable form.
     * @brief The Global Variable form.
     */
    class GlobalVariableForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(char, Type)
        FORM_MEMBER(float, Value)

    public:
        GlobalVariableForm() {}
        GlobalVariableForm(const Form& f);
        ~GlobalVariableForm() {}

        void load(io::Reader &r);
        void addForm() override;
        void readForm() override;

    signals:
        void addGLOB(GlobalVariableForm& form);
        void readGLOB(GlobalVariableForm& form);
    };
}

#endif // GLOBALVARIABLEFORM_H
