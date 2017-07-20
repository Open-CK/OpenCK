/*
** readbytes
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
** Created Date: 12-Jul-2017
*/

#include "readfile.h"

//!@file readfile.cpp Reads data from a file stream.

ReadFile::ReadFile() { }

/**
 * Reads a float from a supplied data stream into a buffer.
 * @brief ReadFile::readFloat
 * @param in The data stream the float is to be read from.
 * @param buffer The buffer the float will be put in.
 * @return
 */
float ReadFile::readFloat(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(), 4);
    QDataStream str(*(buffer));
    return getFloat(&str);
}

/**
 * Reads a string from the supplied data stream into the buffer, returning the string.
 * @brief Reads a string from a data stream into the buffer.
 * @param in The datastream the string is to be read from.
 * @param buffer The buffer the string will be put in.
 * @return The string that was read.
 */
QString ReadFile::readString(QDataStream* in, QByteArray* buffer)
{
    quint8 byte = 0;
    buffer->resize(0);
    buffer->clear();

    do {
        *(in) >> byte;
        buffer->append(byte);
    } while (byte != 0);

    QString str(*(buffer));

    return str;
}

/**
 * Reads a character array from a data stream to a buffer.
 * @brief Reads a char array from a data stream to a buffer.
 * @param in QDataStream character array is read from.
 * @param buffer ByteArray to temporarily store data.
 * @return Character array read from data stream.
 */
char* ReadFile::readChar(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    char* inType = buffer->data();
    return inType;
}

/**
 * Reads a 32 bit signed integer from a data stream to a buffer.
 * @brief Reads a 32 bit signed integer from a stream.
 * @param in QDataStream integer is read from.
 * @param buffer ByteArray to temporarily store data.
 * @return The 32 bit signed integer that was read.
 */
qint32 ReadFile::readInt32_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    qint32 inData = getInt32_t(buffer);
    return inData;
}

/**
 * Reads an unsigned 16 bit integer from a data stream into a buffer.
 * @brief Reads an unsigned 16 bit integer from a data stream.
 * @param in QDataStream integer is read from.
 * @param buffer ByteArray to temporarily store data.
 * @return The unsigned 16 bit integer from the data stream.
 */
quint16 ReadFile::readUInt16_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(2);
    in->readRawData(buffer->data(),2);
    quint16 inData = getUInt16_t(buffer);
    return inData;
}

/**
 * Reads an unsigned 32 bit integer from a data stream into a buffer.
 * @brief Reads an unsigned 32 bit integer from a data stream.
 * @param in QDataStream integer is read from.
 * @param buffer ByteArray to temporarily store data.
 * @return The unsigned 32 bit integer read from the data stream.
 */
quint32 ReadFile::readUInt32_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(4);
    in->readRawData(buffer->data(),4);
    quint32 inData = getUInt32_t(buffer);
    return inData;
}

/**
 * Reads an unsigned 64 bit integer from a data stream into a buffer.
 * @brief Reads an unsigned 64 bit integer from a data stream.
 * @param in QDataStream integer is read from.
 * @param buffer ByteArray to temporarily store data.
 * @return The unsigned 64 bit integer read from the data stream.
 */
quint64 ReadFile::readUInt64_t(QDataStream* in, QByteArray* buffer)
{
    buffer->resize(8);
    in->readRawData(buffer->data(),8);
    quint64 inData = getUInt32_t(buffer);
    return inData;
}

/**
 * Convert a 4-index byte array into a 32 bit signed integer.
 * @brief Convert a byte array into a 32 bit integer.
 * @param array Byte array to convert.
 * @return The 32 bit signed integer read from the byte array.
 */
qint32 ReadFile::getInt32_t(QByteArray* array)
{
    qint32 number = 0;

    for (int i = 0; i < 4; i++) {
        quint8 index = array->at(i);
        quint32 conversion = 0;
        int8_t final = 0;
        qint32 finalConversion = 0;

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

/**
 * Convert a 2-index byte array into a 16 bit unsigned integer.
 * @brief Convert a byte array into a 16 bit unsigned integer.
 * @param array Byte array to convert.
 * @return The 16 bit unsigned integer read from byte array.
 */
quint16 ReadFile::getUInt16_t(QByteArray* array)
{
    quint16 number = 0;
    quint16 conversion = 0;

    for (int i = 0; i < 2; i++) {
        quint8 index = array->at(i);

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
 * Convert a 4-index byte array into a 32 bit unsigned integer.
 * @brief Convert a byte array into a 32 bit unsigned integer.
 * @param array Byte array to convert.
 * @return The 32 bit unsigned integer read from byte array.
 */
quint32 ReadFile::getUInt32_t(QByteArray* array)
{
    quint32 number = 0;
    quint32 conversion = 0;

    for (int i = 0; i < 4; i++) {
        quint8 index = array->at(i);

        if (i == 1 || i == 2 || i == 3) {
            conversion = index * pow(2,(i * 8));
        } else {
            conversion = index;
        }

        number += conversion;
    }

    return number;
}

/**
 * Convert an 8-index byte array into a 64 bit unsigned integer.
 * @brief Convert a byte array into a 64 bit unsigned integer.
 * @param array Byte array to convert.
 * @return The 64 bit unsigned integer read from byte array.
 */
quint64 ReadFile::getUInt64_t(QByteArray* array)
{
    quint64 number = 0;
    quint64 conversion = 0;

    for (int i = 0; i < 8; i++) {
        quint8 index = array->at(i);

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
 * Reads a float value from a data stream.
 * @brief ReadBytes::readFloat
 * @param arrayStream QByteArray stream buffer that the float is read from.
 * @return Float value that is read from the data stream.
 */
float ReadFile::getFloat(QDataStream* arrayStream)
{
    arrayStream->setFloatingPointPrecision(QDataStream::SinglePrecision);
    arrayStream->setByteOrder(QDataStream::LittleEndian);
    float toFloat;
    *(arrayStream) >> toFloat;
    //fix floating point errors that have occured, if any.
    float tmp = toFloat * 10;
    int tmp2 = ((int)tmp) % 10;

    toFloat = tmp/10.0f + tmp2/10;

    return toFloat;
}
