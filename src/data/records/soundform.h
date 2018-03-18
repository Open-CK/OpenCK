/*
** soundform.h
**
** Copyright © Beyond Skyrim Development Team, 2018.
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
** Created Date: 18-Mar-2018
*/

//!@file soundform.h Header for the SOUN record class.

#ifndef SOUNDFORM_H
#define SOUNDFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <data/form.h>
#include <data/subrecords/objectboundsfield.h>

namespace esx
{
    /**
     * The SOUN Form.
     * @brief The SOUN Form.
     */
    class SoundForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(ObjectBoundsField, ObjectBounds)
        FORM_MEMBER(quint32, SoundDataID)

    public:
        SoundForm() : EditorID(""), ObjectBounds{0, 0, 0, 0, 0, 0}, SoundDataID(0) {}
        SoundForm(const Form& f);
        ~SoundForm() {}

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addSOUN(SoundForm& form);
        void readSOUN(SoundForm& form);
    };
}

#endif // SOUNFORM_H
