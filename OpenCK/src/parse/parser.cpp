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

    char typeArray[4];
    char* typeChar = readCharArray(in, &typeBuffer);
    strcpy(typeArray, typeChar);
    memcpy(TES4->entries.type, typeArray, 4);

    TES4->entries.dataSize = readUInt32_t(in, &sizeBuffer);
    TES4->entries.flags = readUInt32_t(in, &flagBuffer);
    TES4->entries.id = readUInt32_t(in, &idBuffer);
    TES4->entries.revision = readUInt32_t(in, &revisionBuffer);
    TES4->entries.version = readUInt32_t(in, &versionBuffer);

    qDebug() << "VALUES: " << TES4->entries.type << TES4->entries.dataSize << TES4->entries.flags <<
        TES4->entries.id << TES4->entries.revision << TES4->entries.version << TES4->entries.unknown;

    QByteArray fieldTypeBuffer;
    QByteArray fieldDataSizeBuffer;
    QByteArray fieldVersionBuffer;
    QByteArray numRecordsBuffer;
    QByteArray objectIdBuffer;

    char fieldTypeArray[4];
    char* fieldType = readCharArray(in, &fieldTypeBuffer);
    strcpy(fieldTypeArray, fieldType);
    memcpy(TES4->HEDR.type, fieldTypeArray, 4);
    TES4->HEDR.dataSize = readUInt16_t(in, &fieldDataSizeBuffer);

    char* temp = readCharArray(in, &fieldVersionBuffer);
    QDataStream stream(fieldVersionBuffer);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    stream.setByteOrder(QDataStream::LittleEndian);
    float fieldVersion;
    stream >> fieldVersion;
    TES4->HEDR.entries.version = fieldVersion;

    TES4->HEDR.entries.numRecords = readInt32_t(in, &numRecordsBuffer);
    TES4->HEDR.entries.nextObjectId = readUInt64_t(in, &objectIdBuffer);

    qDebug() << "New field type:" << fieldType;
}

/**
 * Transfers a character array from file to record object.
 * @brief Parser::readCharArray
 * @param in QDataStream from plugin/master file.
 * @param buffer ByteArray to temporarily store data.
 * @return Character array transferred from file.
 */
char* Parser::readCharArray(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    char* inType = buffer->data();
    return inType;
}

int32_t Parser::readInt32_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    int32_t inData = getInt32_t(buffer);
    return inData;
}

uint16_t Parser::readUInt16_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(2);
    in->readRawData(buffer->data(),2);
    uint16_t inData = getUInt16_t(buffer);
    return inData;
}

/**
 * Transfers an unsigned 32-bit integer from file to record object.
 * @brief Parser::readUInt32_t
 * @param in QDataStream from plugin/master file.
 * @param buffer ByteArray to temporarily store data.
 * @return Integer transferred from file.
 */
uint32_t Parser::readUInt32_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    uint32_t inData = getUInt32_t(buffer);
    return inData;
}

uint64_t Parser::readUInt64_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(8);
    in->readRawData(buffer->data(),8);
    uint64_t inData = getUInt32_t(buffer);
    return inData;
}

int32_t Parser::getInt32_t(QByteArray* array)
{
    int32_t number = 0;

    for (int i = 0; i < 4; i++) {
        uint8_t index = array->at(i);
        uint32_t conversion = 0;
        int8_t final = 0;
        int32_t finalConversion = 0;

        if (i == 1 || i == 2) {
            conversion = index * pow(2,(i * 8));
        } else if (i == 3) {
            final = array->at(i);
            finalConversion = index* pow(2,(i * 8));
        } else {
            conversion = index;
        }

        number += conversion;
        number += finalConversion;
    }

    return number;
}

uint16_t Parser::getUInt16_t(QByteArray* array)
{
    uint16_t number = 0;
    uint16_t conversion = 0;

    for (int i = 0; i < 2; i++) {
        uint8_t index = array->at(i);

        if (i == 1) {
            conversion = index * pow(2,8);
        } else {
            conversion = index;
        }

        number += conversion;
    }

    return number;
}

/**
 * Convert a 4-index byte array into a 32-bit unsigned integer.
 * @brief Parser::getUInt32_t
 * @param array Byte array to convert.
 * @return Integer value.
 */
uint32_t Parser::getUInt32_t(QByteArray* array)
{
    uint32_t number = 0;
    uint32_t conversion = 0;

    for (int i = 0; i < 4; i++) {
        uint8_t index = array->at(i);

        if (i == 1 || i == 2 || i == 3) {
            conversion = index * pow(2,(i * 8));
        } else {
            conversion = index;
        }

        number += conversion;
    }

    return number;
}

uint64_t Parser::getUInt64_t(QByteArray* array)
{
    uint64_t number = 0;
    uint64_t conversion = 0;

    for (int i = 0; i < 8; i++) {
        uint8_t index = array->at(i);

        if (i == 1 || i == 2 || i == 3 || i == 4 || i == 5
            || i == 6 || i == 7) {
            conversion = index * pow(2,(i * 8));
        } else {
            conversion = index;
        }

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

