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
        Reader(QDataStream* filestream)
        {
            this->filestream = filestream;
        }

        template <typename T>
        inline T read()
        {
            T data;
            buffer.resize(sizeof(T));
            filestream->readRawData(buffer.data(), sizeof(T));
            memcpy(&data, buffer.data(), sizeof(T));

            return data;
        }

        inline quint32 readType()
        {
            quint32 type = read<quint32>();

            return (type >> 24 |
                    ((type << 8) & 0x00FF0000) |
                    ((type >> 8) & 0x0000FF00) |
                    type << 24);
        }

        QString readString(quint32 size)
        {
            QString string("");
            string.resize(size);

            buffer.resize(size);
            filestream->readRawData(buffer.data(), size);
            memcpy(&string, buffer.data(), size);

            return string;
        }

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
        QDataStream* filestream;
        QByteArray buffer;
    };
}

#endif // READER_H
