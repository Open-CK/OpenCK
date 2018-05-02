/*
** imagespaceform.h
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
** Created Date: 02-May-2018
*/

#ifndef IMAGESPACEFORM_H
#define IMAGESPACEFORM_H

#define FORM_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <data/form.h>

namespace esx
{
    class ImagespaceForm : public Form 
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
    public:
        ImagespaceForm();
        ImagespaceForm(const Form& form);
        ~ImagespaceForm() = default;

        void load(io::Reader& r) override;
        void addForm() override;
        void readForm() override;

    signals:
        void addIMGS(ImagespaceForm& IMGS);
        void readIMGS(ImagespaceForm& IMGS);

    private:
    };
}

#endif