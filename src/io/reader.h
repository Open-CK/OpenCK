/*
** readbytes.h
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing filestream the file LICENSE.GPL included filestream the
** packaging of this file.
**
** OpenCK is distributed filestream the hope that it will be useful,
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
** Created Date: 12-Jul-2017
*/

//!@file reader.h Functions to read raw data from the file stream.

#ifndef READER_H
#define READER_H

#include <stdint.h>
#include <QDataStream>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QStandardPaths>

namespace io
{
    /**
     * Static class from which files are read.
     * @brief Static class from which files are read.
     */
    class Reader
    {
    public:
        /**
         * Initialise a new reader object with a pointer to the file stream.
         * @brief Initialise a new reader object.
         * @param filestream Pointer to the file stream.
         */
        Reader(QDataStream* filestream)
        {
            this->filestream = filestream;
        }

        /**
         * Template function that reads from the file stream to any primitive type.
         * @brief Reads data from stream to any primitive type.
         * @returns Data to be read as a primitive type.
         */
        template <typename T>
        inline T read()
        {
            T data;
            buffer.resize(sizeof(T));
            filestream->readRawData(buffer.data(), sizeof(T));
            memcpy(&data, buffer.data(), sizeof(T));

            return data;
        }

        /**
         * Read the type code of a record or subrecord header.
         * @brief Read a type code from stream.
         * @return Type code.
         */
        inline quint32 readType()
        {
            quint32 type = read<quint32>();

            return (type >> 24 |
                    ((type << 8) & 0x00FF0000) |
                    ((type >> 8) & 0x0000FF00) |
                    type << 24);
        }

        /**
         * Read a string of known length from the file stream.
         * @brief Read a string of known length.
         * @param size Length of string.
         * @return String.
         */
        QString readString(quint32 size)
        {
            QString string("");
            string.resize(size);

            buffer.resize(size);
            filestream->readRawData(buffer.data(), size);
            memcpy(&string, buffer.data(), size);

            return string;
        }

        /**
         * Read a string of size specified in file stream (byte).
         * @brief Read a string of size specified in file stream.
         * @return String.
         */
        QString readBstring()
        {
            quint8 size = read<quint8>();
            QString string("");
            string.resize(size);

            buffer.resize(size);
            filestream->readRawData(buffer.data(), size);
            memcpy(&string, buffer.data(), size);

            return string;
        }

        /**
         * Read a string of size specified in file stream (word/int16).
         * @brief Read a string of size specified in file stream.
         * @return String.
         */
        QString readWstring()
        {
            quint16 size = read<quint16>();
            QString string("");
            string.resize(size);

            buffer.resize(size);
            filestream->readRawData(buffer.data(), size);
            memcpy(&string, buffer.data(), size);

            return string;
        }

        /**
         * Read a zero-terminated string from the file stream.
         * @brief Read a zero-terminated string.
         * @return String.
         */
        QString readZstring()
        {
            quint8 byte = 0;
            QString string("");

            do {
                byte = read<quint8>();
                string.append(byte);
            }
            while (byte != 0);

            return string;
        }

        //TEMPORARY FUNCTION
        /**
         * Look up and retrieve a localised string from strings file using an index.
         * @brief lookupString Look up and retrieve a localised string.
         * @param filename Name of streamed file.
         * @param index String ID.
         * @param recordType Type code of record requesting lookup.
         * @param subrecord Type code of subrecord requesting lookup.
         * @return String.
         */
        QString lookupString(QString filename, quint32 index, quint32 recordType, quint32 subrecord)
        {
            //Get the filename without extensions (Update.esm->Update)
            QString temp = filename;
            QString file;
            int lastindex = temp.lastIndexOf(".");
            file = temp.left(lastindex);

            //Get the type of string table
            QString extension;
            if(recordType != 'LSCR' && subrecord == 'DESC') {
                extension = ".DLSTRINGS";
            } else if(recordType == 'QUST' && subrecord == 'CNAM') {
                extension = ".DLSTRINGS";
            } else if(recordType == 'BOOK' && subrecord == 'CNAM') {
                extension = ".DLSTRINGS";
            } else if(recordType == 'INFO' && subrecord != 'RNAM') {
                extension = ".ILSTRINGS";
            } else {
                extension = ".STRINGS";
            }

            //Get the language from the ini file
            QString documents = QString("%1/My Games/Skyrim/Skyrim.ini")
                    .arg(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
            qDebug() << "Documents folder is " << documents;
            QSettings ini(documents, QSettings::IniFormat);

            QString language = ini.value("sLanguage", "English").toString();
            language = language.toLower().replace(0,1,language.at(0).toUpper());
            qDebug() << "Language is " << language;

            //Get the strings directory
            QDir dir = QCoreApplication::applicationDirPath().append("/");
            dir.cd("./Data/Strings/");
            QFile table = dir.path().append("/").append(file).append("_").
                    append(language).append(extension);
            qDebug() << "Table is " << table.fileName();

            if(!table.exists()) {
                return "Error: File not found!";
            }
            qDebug() << "String table lookup file found is " << table.fileName();

            return "TODO";
        }

    private:
        /**
         * Pointer to the file stream.
         * @brief filestream Pointer to the file stream.
         */
        QDataStream* filestream;

        /**
         * Buffer to store binary data temporarily.
         * @brief buffer Buffer to store data.
         */
        QByteArray buffer;
    };
}

#endif // READER_H
