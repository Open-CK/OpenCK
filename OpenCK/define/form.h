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

#include <stdint.h>
#include <array>
#include <QChar>
#include <QtEndian>

#include "readfile.h"

namespace Define
{
    enum class SubrecordName;
    enum class FormName;
    struct SubrecordHeader;
    struct FormHeader;
    class Form;
}

/**
 * The enum for the name of a parsed subrecord.
 * @brief The type of subrecord.
 */
enum class SubrecordName
{
    Header_Data, Author_Information, Description, Master_Files,
    Overriden_Forms, Internal_Version, Unknown_Value
};

/**
 * The enum for the name of the Form.
 * @brief The name of the Form.
 */
enum class FormName
{
    Header
};

/**
 * The parsed header for each individual parsed subrecord.
 * @brief The parsed header for each subrecord.
 */
struct SubrecordHeader
{
    /**
     * The type of the subrecord. Stored in a uin32_t for efficient integer comparison.
     * @brief The type of subrecord.
     */
    quint32 type;
    /**
     * The binary size, in bytes, of the subrecord data data entry.
     * @brief The byte size of the subrecord data entry.
     */
    quint16 size;
};

/**
 * The header of the form which contains nonparsed needed information.
 * @brief The header of the nonparsed form.
 */
struct FormHeader
{
    /**
     * The type of the form. Stored in a uint32 for efficient integer comparison.
     * @brief The type of the form in binary.
     */
    quint32 type;
    /**
     * The size of the data in the form, in bytes.
     * @brief The size of the data in the form.
     */
    quint32 dataSize;
    /**
     * The flags (if any) of the form.
     * @brief The flags of the form.
     */
    quint32 flags;
    /**
     * The form identifier.
     * @brief The form identifier.
     */
    quint32 id;
    /**
     * The id used for revision control.
     * @brief The revision control id.
     */
    quint32 revision;
    /**
     * The version of an unknown entity, but it exists in the form header nonetheless.
     * @brief The version of an unknown entity.
     */
    quint32 version;
    /**
     * An unknown value, but it exists in the form header nonetheless.
     * @brief Unknown.
     */
    quint16 unknown;
};

/**
 * The abstract class that is the base for all parsed forms in .esp and .esm files.
 * @brief The base class for forms in .esp and .esm files.
 */
class Form
{
public:
    Form();
    virtual ~Form();
    /**
     * Loads a form from a data stream.
     * @brief Loads a form from a datastream.
     * @param in Datastream to be read from.
     */
    virtual void load(QDataStream* in) = 0;
    SubrecordHeader readSubrecord(QDataStream* in, quint32* read);

protected:
    /**
     * The name of the form.
     * @brief Name of the form.
     */
    FormName name;
    /**
     * The header of the form, with needed data for the parser.
     * @brief The form's header.
     */
    FormHeader header;
};

#endif // FORM_H
