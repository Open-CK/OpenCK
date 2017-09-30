#include "txstform.h"

TXSTForm::TXSTForm()
{

}

TXSTForm::~TXSTForm()
{

}

TXSTForm::load(QDataStream *in, int fileNumber)
{
    QByteArray buffer;

    header.type = qToBigEndian(ReadFile::readUInt32(in, &buffer));
    header.dataSize = ReadFile::readUInt32(in, &buffer);
    header.flags = ReadFile::readUInt32(in, &buffer);
    header.id = ReadFile::readUInt32(in, &buffer);
    header.revision = ReadFile::readUInt32(in, &buffer);
    header.version = ReadFile::readUInt16(in, &buffer);
    header.unknown = ReadFile::readUInt16(in, &buffer);

    quint32 sizeRead = 0;
    readSubrecord(in, &temp);
    editorID = ReadFile::readString(in, &sizeRead);
    sizeRead += editorID.length() + 1;

    for (int i = 0; i < 12; i++) {
        readSubrecord(in, &temp);
        unknownArray[i] = ReadFile::readUByte(in, &buffer);
    }

    sizeRead += 12;

    while (sizeRead < header.dataSize) {
        SubrecordHeader nextRecord = readSubrecord(in, &sizeRead);

        switch (header.type) {
            //Texture paths
            case "TX00":
                map00 = ReadFile::readString(in, &buffer);
                sizeRead += map00.length() + 1;
                break;
            case "TX01":
                map01 = ReadFile::readString(in, &buffer);
                sizeRead += map01.length() + 1;
                break;
            case "TX02":
                map02 = ReadFile::readString(in, &buffer);
                sizeRead += map02.length() + 1;
                break;
            case "TX03":
                map03 = ReadFile::readString(in, &buffer);
                sizeRead += map03.length() + 1;
                break;
            case "TX04":
                map04 = ReadFile::readString(in, &buffer);
                sizeRead += map04.length() + 1;
                break;
            case "TX05":
                map05 = ReadFile::readString(in, &buffer);
                sizeRead += map05.length() + 1;
                break;
            case "TX06":
                map06 = ReadFile::readString(in, &buffer);
                sizeRead += map06.length() + 1;
                break;
            case "TX07":
                map07 = ReadFile::readString(in, &buffer);
                sizeRead += map07.length() + 1;
                break;
            //Decal data
            case "DODT":
                readDecalData(in, &buffer);
                sizeRead += sizeof(DecalData);
                break;
            case "DNAM":
                textureFlags = ReadFile::readUInt16(in, &buffer);
                sizeRead += sizeof(uint16_t);
                break;
        }
    }
}

void TXSTForm::readDecalData(QDataStream *in, QByteArray *buffer)
{
    decalData.minWidth = ReadFile::readFloat(in, buffer);
    decalData.maxWidth = ReadFile::readFloat(in, buffer);
    decalData.minHeight = ReadFile::readFloat(in, buffer);
    decalData.maxHeight = ReadFile::readFloat(in, buffer);
    decalData.depth = ReadFile::readFloat(in, buffer);
    decalData.shininess = ReadFile::readFloat(in, buffer);
    decalData.parallaxScale = ReadFile::readFloat(in, buffer);
    decalData.parrallaxPasses = ReadFile::readUByte(in, buffer);
    decalData.decalFlags = ReadFile::readUByte(in, buffer);
    decalData.unknown00 = ReadFile::readUByte(in, buffer);
    decalData.unknown01 = ReadFile::readUByte(in, buffer);
    decalData.rgb = ReadFile::readUInt32(in, buffer);
}

QString TXSTForm::getEditorID() const
{
    return editorID;
}

quint8* TXSTForm::getUnknownArray() const
{
    return unknownArray;
}

QString TXSTForm::getMap00() const
{
    if (map00 == nullptr) {
        return "ERROR";
    }
    else return map00;
}

QString TXSTForm::getMap01() const
{
    if (map01 == nullptr) {
        return "ERROR";
    }
    else return map01;
}

QString TXSTForm::getMask02() const
{
    if (map02 == nullptr) {
        return "ERROR";
    }
    else return map02;
}

QString TXSTForm::getMap03() const
{
    if (map03 == nullptr) {
        return "ERROR";
    }
    else return map03;
}

QString TXSTForm::getMap04() const
{
    if (map04 == nullptr) {
        return "ERROR";
    }
    else return map04;
}

QString TXSTForm::getMap05() const
{
    if (map05 == nullptr) {
        return "ERROR";
    }
    else return map05;
}

QString TXSTForm::getMap06() const
{
    if (map06 == nullptr) {
        return "ERROR";
    }
    else return map06;
}

QString TXSTForm::getMap07() const
{
    if (map07 == nullptr) {
        return "ERROR";
    }
    else return map07;
}

DecalData getDecalData() const
{
    return decalData;
}

quint16 TXSTForm::getTextureFlags() const
{
    return textureFlags;
}

void TXSTForm::setEditorID(const QString in)
{
    editorID = in;
}

void setUnknownArray(const quint8* start)
{
    unknown00 = *(start);
    start++;
    unknown01 = *(start);
}

void setMap00(const QString path)
{
    map00 = in;
}

void setMap01(const QString path)
{
    map01 = in;
}

void setMap02(const QString path)
{
    map02 = in;
}

void setMap03(const QString path)
{
    map03 = in;
}

void setMap04(const QString path)
{
    map04 = in;
}

void setMap05(const QString path)
{
    map05 = in;
}

void setMap06(const QString path)
{
    map06 = in;
}

void setMap07(const QString path)
{
    map07 = in;
}

void setDecalData(const DecalData in)
{
    DecalData = in;
}

void setTextureFlags(const quint16 in)
{
    textureFlags = in;
}
