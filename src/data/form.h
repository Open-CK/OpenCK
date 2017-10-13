/*
** recordparent.h
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

//!@file form.h Header for the abstract form class.

#ifndef FORM_H
#define FORM_H

#define FORMHEADER_MEMBER(type, name) \
private: \
    type name; \
public: \
    const type& get##name##() const { return name; } \
    void set##name##(const type& newval) { name = newval; }

#include <stdint.h>
#include <array>
#include <QChar>
#include <QtEndian>
#include <QObject>

#include "reader.h"

namespace esx
{
    /**
     * The enum for the name of the Form.
     * @brief The name of the Form.
     */
    enum FormName
    {
        Default,
        TES4,
        GameSetting,
        Keyword,
        LocationReferenceType,
        Action,
        TextureSet
    };

    typedef FormName formName;

    /**
     * The parsed header for each individual parsed subrecord.
     * @brief The parsed header for each subrecord.
     */
    struct SubrecordHeader
    {
        quint32 type;
        quint16 size;
    };

    /**
     * The header of the form which contains nonparsed needed information.
     * @brief The header of the nonparsed form.
     */
    class FormHeader
    {
        FORMHEADER_MEMBER(formName, Name)
        FORMHEADER_MEMBER(quint32, Type)
        FORMHEADER_MEMBER(quint32, DataSize)
        FORMHEADER_MEMBER(quint32, Flags)
        FORMHEADER_MEMBER(quint32, ID)
        FORMHEADER_MEMBER(quint32, Revision)
        FORMHEADER_MEMBER(quint32, Version)
        FORMHEADER_MEMBER(quint16, Unknown)
    };

    /**
     * The abstract class that is the base for all parsed forms in .esp and .esm files.
     * @brief The base class for forms in .esp and .esm files.
     */
    class Form : public QObject
    {
    public:
        Form() {}
        virtual ~Form() {}

        virtual void load(io::Reader& r) {}
        virtual void addForm() {}
        virtual void readForm() {}

        void readHeader(io::Reader& r, const quint32 type);
        FormHeader getHeader() const;
        SubrecordHeader readSubrecord(io::Reader& r, quint32* read);
        quint32 getSize() const;

    protected:
        /**
         * Form header.
         * @brief header Form header.
         */
        FormHeader header;
    };
}

#endif // FORM_H
