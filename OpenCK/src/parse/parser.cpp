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

        //Begin parsing header record
        TES4Record* TES4 = new TES4Record;
        readHeader(&in, TES4);
        qDebug() << "Done parsing header struct, put a breakpoint on this line and check variable list.";

//      while(!in.atEnd()) {
//          //get the non-header data.
//      }

//      Parsed justParsed(TES4 /* more data, but just doing headerdata right now */);
//      parsed.append(justParsed);
    }
}

/**
 * Fill record details for header.
 * @brief Parser::readHeader
 * @param in QDataStream from plugin/master file.
 * @param TES4 Record to be populated.
 */
void Parser::readHeader(QDataStream* in, TES4Record* TES4)
{
    QByteArray typeBuffer;
    QByteArray sizeBuffer;
    QByteArray flagBuffer;
    QByteArray idBuffer;
    QByteArray revisionBuffer;
    QByteArray versionBuffer;
    QByteArray unknownBuffer;

    char typeArray[4];
    char* typeChar = ReadBytes::readCharArray(in, &typeBuffer);
    strcpy(typeArray, typeChar);
    memcpy(TES4->entries.type, typeArray, 4);

    TES4->entries.dataSize = ReadBytes::readUInt32_t(in, &sizeBuffer);
    TES4->entries.flags = ReadBytes::readUInt32_t(in, &flagBuffer);
    TES4->entries.id = ReadBytes::readUInt32_t(in, &idBuffer);
    TES4->entries.revision = ReadBytes::readUInt32_t(in, &revisionBuffer);
    TES4->entries.version = ReadBytes::readUInt16_t(in, &versionBuffer);
    TES4->entries.unknown = ReadBytes::readUInt16_t(in, &unknownBuffer);

    QByteArray fieldTypeBuffer;
    QByteArray fieldDataSizeBuffer;
    QByteArray fieldVersionBuffer;
    QByteArray numRecordsBuffer;
    QByteArray objectIdBuffer;

    char fieldTypeArray[4];
    char* fieldType = ReadBytes::readCharArray(in, &fieldTypeBuffer);
    strcpy(fieldTypeArray, fieldType);
    memcpy(TES4->HEDR.type, fieldTypeArray, 4);
    TES4->HEDR.dataSize = ReadBytes::readUInt16_t(in, &fieldDataSizeBuffer);

    char* temp = ReadBytes::readCharArray(in, &versionBuffer);
    QDataStream stream(versionBuffer);
    TES4->HEDR.entries.version = ReadBytes::readFloat(in, &stream);
    TES4->HEDR.entries.numRecords = ReadBytes::readInt32_t(in, &numRecordsBuffer);
    TES4->HEDR.entries.nextObjectId = ReadBytes::readUInt64_t(in, &objectIdBuffer);

    qDebug() << "New field type:" << fieldType;
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

/**
 * Provides an error message box containing a given string.
 * @brief Parser::warn
 * @param message Message to be displayed in the warning box.
 */
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

