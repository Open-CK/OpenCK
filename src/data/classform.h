/*
** classform.h
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
** Created Date: 17-Oct-2017
*/

//!@file classform.h Header for the Class form class.

#ifndef CLASSFORM_H
#define CLASSFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include "form.h"

namespace esx
{
    /**
     * Stores various class data and attributes.
     * @brief The ClassInf struct for class attributes.
     */
    struct ClassInf
    {
        quint32 unknown;
        quint8 trainingSkill;
        quint8 trainingLevel;
        quint8 skillWeights[18];
        float bleedoutDefault;
        quint32 voicePoints;
        quint8 healthWeight;
        quint8 magickaWeight;
        quint8 staminaWeight;
        quint8 flags;
    };

    typedef ClassInf classInf;

    /**
     * The Class form.
     * @brief The Class Form.
     */
    class ClassForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(quint32, FullName)
        FORM_MEMBER(quint32, Desc)
        FORM_MEMBER(QString, Icon)
        FORM_MEMBER(classInf, ClassData)

    public:
        ClassForm() {}
        ClassForm(const Form &f);
        ~ClassForm() {}

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override {}

    signals:
        void addCLAS(ClassForm& form);
        void readCLAS(ClassForm& form);
    };
}

#endif // CLASSFORM_H
