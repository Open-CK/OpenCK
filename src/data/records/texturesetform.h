/*
** texturesetform.h
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
** Created Date: 13-Oct-2017
*/

//!@file texturesetform.h Header for the TXST record class.

#ifndef TEXTURESETFORM_H
#define TEXTURESETFORM_H

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
    struct DecalInf
    {
        float minWidth;
        float maxWidth;
        float minHeight;
        float maxHeight;
        float depth;
        float shininess;
        float parallaxScale;
        quint8 parallaxPasses;
        quint8 flags;
        quint8 unknown[2];
        quint32 color;
    };

    typedef DecalInf DecalInf;

    class TextureSetForm : public Form
    {
        Q_OBJECT

        FORM_MEMBER(QString, EditorID)
        FORM_MEMBER(DecalInf, DecalData)
        FORM_MEMBER(quint16, Flags)
        FORM_MEMBER(ObjectBoundsField, ObjectBounds)

    public:
        TextureSetForm() {}
        TextureSetForm(const Form& f);
        ~TextureSetForm() {}

        void load(io::Reader& r);
        void addForm();
        void readForm();

        void setPath(const quint8 n, const QString& in);
        QString getPath(const quint8 n) const;
        bool hasDODT() const;
        bool hasTextureFlags() const;

    private:
        QString paths[8];
        bool hasDecalData = false;
        bool hasFlags = false;

    signals:
        void addTXST(TextureSetForm& form);
        void readTXST(TextureSetForm& form);
    };
}

#endif // TEXTURESETFORM_H
