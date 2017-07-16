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

#ifndef FORM_H
#define FORM_H

#include <stdint.h>
#include <array>
#include <QChar>

#include "readfile.h"

namespace Define
{
    enum class SubrecordName;
    enum class FormName;
    struct SubrecordHeader;
    struct FormHeader;
    class Form;
}

enum class SubrecordName
{
    Header_Data, Author_Information, Description, Master_Files,
    Overriden_Forms, Internal_Version, Unknown_Value
};

enum class FormName
{
    Header
};

struct SubrecordHeader
{
    uint32_t type;
    uint16_t size;
};

struct FormHeader
{
    uint32_t type;
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
    uint32_t version;
    uint16_t unknown;
};

class Form
{
public:
    Form();
    virtual ~Form();
    virtual void load(QDataStream *in) = 0;

protected:
    FormName name;
    FormHeader header;
};

#endif // FORM_H
