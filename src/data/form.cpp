/*
** form.cpp
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

#include <data/form.h>
#include <io/reader.h>

//!@file form.cpp Source for parsing Forms from .esm and .esp files.

namespace esx
{
    /**
     * Loads the GMST header from the data stream.
     * @brief Loads the header.
     * @param r Reader object that performs all parsing functions.
     * @param read Pointer to Integer representing the amount of bytes read.
     * @return Subrecord header.
     */
    SubrecordHeader Form::readSubrecord(io::Reader& r, quint32* read)
    {
        SubrecordHeader h;
        h.type = r.readType();
        h.size = r.read<quint16>();
        *read += 6;

        if (h.type == 'XXXX') {
            h.size = r.read<quint16>();
            quint32 type = r.readType();
            r.read<quint16>();
            *read += 10;
        }

        return h;
    }

    /**
     * Reads record header values from file.
     * @brief Reads a record header.
     * @param r Provides raw data reading functionality.
     * @param type Record type code, identified by parser.
     */
    void Form::readHeader(io::Reader& r, const quint32 type)
    {
        this->header.setName(FormName::Default);
        this->header.setType(type);
        this->header.setDataSize(r.read<quint32>());
        this->header.setFlags(r.read<quint32>());
        this->header.setID(r.read<quint32>());
        this->header.setRevision(r.read<quint32>());
        this->header.setVersion(r.read<quint16>());
        this->header.setUnknown(r.read<quint16>());
    }

    /**
     * Retrieve the header from a form.
     * @brief Retrieve form header.
     * @return Form header.
     */
    FormHeader Form::getHeader() const
    {
        return header;
    }

    /**
     * Retrieve the size of the form.
     * @brief Retrieve form size.
     * @return Form size.
     */
    quint32 Form::getSize() const
    {
        return header.getDataSize() + 24; //Size of data fields + header size
    }
}
