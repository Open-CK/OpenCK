#include "esmreader.h"

#include <sstream>

ESMReader::ESMReader(const QString& path)
    : esm(path)
{

}

ESMReader::~ESMReader()
{

}

void ESMReader::open()
{
    esm.file.close();
    stream.setDevice(&esm.file);

    if (!esm.file.open(QIODevice::ReadWrite))
    {
        auto exists = esm.file.exists();
        auto error = esm.file.error();
        std::ostringstream oss;
        oss << "Error: cannot open data file \""
            << esm.file.fileName().toStdString()
            << "\".";
        throw std::runtime_error(oss.str());
    }

    if (readName() != 'TES4')
    {
        notifyFailure("not a valid Skyrim file!");
    }

    header.load(*this);
    auto debug = true;
}

NAME ESMReader::readName()
{
    NAME name;
    buf.resize(sizeof(NAME));
    stream.readRawData(buf.data(), sizeof(NAME));
    memcpy(&name, buf.data(), sizeof(NAME));
    esm.forward(sizeof(NAME));
    return swapName(name);
}

bool ESMReader::isNextName(NAME name)
{
    NAME cmp;
    buf.resize(sizeof(NAME));
    esm.file.peek(buf.data(), sizeof(NAME));
    memcpy(&cmp, buf.data(), sizeof(NAME));
    return swapName(cmp) == name;
}

RecHeader ESMReader::readHeader()
{
    RecHeader header;
    header.size = readType<quint32>();
    esm.recLeft = header.size;
    esm.subLeft = 0;

    header.flags = readType<quint32>();
    header.id = readType<quint32>();
    header.vcDay = readType<quint8>();
    header.vcMonth = readType<quint8>();
    header.vcLastUser = readType<quint8>();
    header.vcCurrUser = readType<quint8>();
    header.version = readType<quint16>();
    header.unknown = readType<quint16>();

    return header;
}

NAME ESMReader::readNSubHeader()
{
    NAME name{ readName() };
    quint16 sz = readType<quint16>();
    esm.subLeft = sz;

    return name;
}

bool ESMReader::isRecLeft()
{
    return esm.recLeft > 0;
}

bool ESMReader::isSubLeft()
{
    return esm.subLeft > 0;
}

QString ESMReader::readZString()
{
    const quint16 sz = static_cast<quint16>(esm.subLeft);
    buf.resize(sz);
    stream.readRawData(buf.data(), sz);
    esm.forward(sz);
    return QString(QByteArray(buf));
}

void ESMReader::notifyFailure(const QString& msg)
{
    std::ostringstream oss;
    oss << "Error: " << msg.toStdString()
        << "\nFile: " << esm.file.fileName().toStdString()
        << "\nOffset: "
        << QString("0x%1").arg(esm.size - esm.left, 0, 16).toUpper().toStdString();
    throw std::runtime_error(oss.str());
}

const Header& ESMReader::getHeader()
{
    return header;
}
