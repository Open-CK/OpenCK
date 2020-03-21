#include "strings.hpp"

#include <QDataStream>

Strings::Strings()
{

}

void Strings::load(QString filename, const FilePaths& paths)
{
    // TODO: Replace with application settings value
    QString defaultLanguage = "English";

    QFileInfo info(filename);
    QString filenameOnly = info.fileName();

    int extensionIndex = filenameOnly.lastIndexOf(".");
    QString filenameTrimmed = filenameOnly.remove(extensionIndex, filenameOnly.size() - extensionIndex);

    filename = filenameTrimmed + "_" + defaultLanguage;

    QDir dir = paths.dataDir;
    dir.cd("Strings");

    for (int i = 0; i < Type::NumTypes; i++)
    {
        QString stringsFilename = dir.absolutePath() + "/" + filename + "." + typeExtensions[i];

        QFile file(stringsFilename);

        if (!file.open(QIODevice::ReadOnly))
        {
            continue;
        }

        switch (i)
        {
        case Type::LString:
        {
            loadLStrings(file);
        }
        case Type::ILString:
        {
            loadILStrings(file);
        }
        case Type::DLString:
        {
            loadDLStrings(file);
        }
        }
    }
}

void Strings::loadLStrings(QFile& file)
{
    unsigned int count = readHeader(file);

    QByteArray all = file.readAll();

    QByteArrayList bytesList = all.split('\0');

    for (const auto& bytes : bytesList)
    {
        QString entry = QString::fromLatin1(bytes.data(), bytes.size());

        strings.push_back(entry);
    }
}

void Strings::loadILStrings(QFile& file)
{

}

void Strings::loadDLStrings(QFile& file)
{

}

unsigned int Strings::readHeader(QFile& file)
{
    QDataStream stream;
    stream.setDevice(&file);

    unsigned int count;
    unsigned int dataSize;

    QByteArray buf;
    buf.resize(sizeof(int));
    stream.readRawData(buf.data(), sizeof(int));
    memcpy(&count, buf.data(), sizeof(int));

    buf.clear();
    buf.resize(sizeof(int));
    stream.readRawData(buf.data(), sizeof(int));
    memcpy(&dataSize, buf.data(), sizeof(int));

    stream.skipRawData(count * sizeof(int) * 2);

    return count;
}

QString Strings::get(Type type, unsigned int index) const
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() > index)
    {
        return QString("");
    }
    else
    {
        return stringlist[index];
    }
}

bool Strings::set(Type type, unsigned int index, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() <= index)
    {
        stringlist[index] = entry;

        return true;
    }
    else
    {
        return false;
    }
}

unsigned int Strings::append(Type type, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    stringlist.push_back(entry);

    return stringlist.size() - 1;
}

bool Strings::remove(Type type, unsigned int index)
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() <= index)
    {
        stringlist.remove(index);

        return true;
    }
    else
    {
        return false;
    }
}

unsigned int Strings::find(Type type, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    return stringlist.indexOf(entry);
}

QVector<QString> Strings::selectList(Type type) const
{
    switch (type)
    {
    case Type::LString:
    {
        return strings;
    }
    case Type::ILString:
    {
        return ilstrings;
    }
    case Type::DLString:
    {
        return dlstrings;
    }
    }
}
