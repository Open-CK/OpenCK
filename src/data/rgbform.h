/*
** colorform.h
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
** Created Date: 14-Aug-2017
*/

//!@file texturesetform.h Header for the generic RGB record class.

#ifndef RGBFORM_H
#define RGBFORM_H

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
     * The RGB Form.
     * @brief The RGB Form.
     */
    class RgbForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(quint32, Rgb)

    public:
        RgbForm() {}
        RgbForm(const Form& f);
        ~RgbForm() {}

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addRGB(RgbForm& form);
        void readRGB(RgbForm& form);
    };
}

#endif // RGBFORM_H
