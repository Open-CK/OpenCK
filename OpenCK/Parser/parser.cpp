/*
** parser.cpp
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
** Created Date: 08-Jul-2017
*/

#include "parser.h"

static QList<Parsed> parsed;

/**
 * A debug function to test things without actually writing to file and screwing things up.
 */
void Parser::debug(QStringList list)
{
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        QFileInfo info(file.fileName());
        QString name(info.fileName());
        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadOnly)) {
            warn(name.append(" could not be opened."));
            continue;
        }
        QDataStream in(&file);
        TES4Record* TES4 = new TES4Record;
        QByteArray buffer;
        buffer.resize(4);
        in.readRawData(buffer.data(),4);
        char* inType = buffer.data();
        qDebug() << "Record type is " << inType;
        TES4->type = inType;
    }
}

/**
 * Parses a list of .esm and .esp files (based on file path).
 * Defaults activePath to the first element of the list.
 * @brief Parser::parse
 * @param list The list of files to be parsed.
 * @see Parser::parse(QStringList,QString)
 */
void Parser::parse(QStringList list)
{
    qDebug() << "No active file, defaulting.";
    warn("There is no active file. Defaulting Active File to first selected element.");
    parse(list,list.at(0));
    //debug(list);
}

/**
 * Parses a list of .esm and .esp files (based on file path) with a specified active file.
 * @brief Parser::parse
 * @param list The list of file paths to be parsed.
 * @param activePath the Active File (the file on which changes are applied to).
 */
void Parser::parse(QStringList list, QString activePath)
{
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        QFileInfo info(file.fileName());
        QString name(info.fileName());
        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadOnly)) {
            warn(name.append(" could not be opened."));
            continue;
        }

        QDataStream in(&file);

        TES4Record* TES4 = new TES4Record;
        QByteArray typeBuffer;
        QByteArray sizeBuffer;
        QByteArray flagBuffer;
        QByteArray idBuffer;
        QByteArray revisionBuffer;
        QByteArray versionBuffer;

        typeBuffer.resize(4);
        in.readRawData(typeBuffer.data(),4);
        char* inType = typeBuffer.data();
        TES4->type = inType;

        sizeBuffer.resize(4);
        in.readRawData(sizeBuffer.data(),4);
        uint32_t inDataSize = getUInt32_t(sizeBuffer);
        TES4->dataSize = inDataSize;

        flagBuffer.resize(4);
        in.readRawData(flagBuffer.data(),4);
        uint32_t inFlags = getUInt32_t(flagBuffer);
        TES4->flags = inFlags;

        idBuffer.resize(4);
        in.readRawData(idBuffer.data(),4);
        uint32_t inId = getUInt32_t(idBuffer);
        TES4->id = inId;

        revisionBuffer.resize(4);
        in.readRawData(revisionBuffer.data(),4);
        uint32_t inRevision = getUInt32_t(revisionBuffer);
        TES4->revision = inRevision;

        versionBuffer.resize(4);
        in.readRawData(versionBuffer.data(),4);
        uint32_t inVersion = getUInt32_t(versionBuffer);
        TES4->version = inVersion;

//        while(!in.atEnd()) {
//            //get the non-header data.
//        }

//        Parsed justParsed(TES4 /* more data, but just doing headerdata right now */);
//        parsed.append(justParsed);
    }
}

uint32_t Parser::getUInt32_t(QByteArray array)
{
    uint32_t number = 0;

    for (int i = 0; i < array.length(); i++) {
        uint8_t conversion = array[i];
        number += conversion;
    }

    return number;
}

/**
 * Returns a parsed collection of .esm and .esp files.
 * @brief Parser::getParsed
 * @return The list of parsed objects based on #parse
 * @see Parser::parse(QStringList)
 */
QList<Parsed> Parser::getParsed()
{
    return parsed;
}

void Parser::warn(QString message)
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setSizeIncrement(600, 400);
    msgBox->setText(message);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowIcon(QIcon(":/openck32x32.png"));
    msgBox->exec();
}

