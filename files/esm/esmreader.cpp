#include "esmreader.h"

#include <sstream>

ESMReader::ESMReader(const QString& path, const QString& name)
    : file(path),
      fileName(name)
{

}

ESMReader::~ESMReader()
{

}

void ESMReader::open()
{
    file.close();
    startStream();

    if (!file.open(QIODevice::ReadWrite))
    {
        std::ostringstream oss;
        oss << "Error: cannot open data file \""
            << file.fileName().toStdString()
            << "\".";
        throw std::runtime_error(oss.str());
    }

    if (readName() != 'TES3')
    {
        notifyFailure("not a valid Skyrim file!");
    }
}

void ESMReader::startStream()
{
    size = file.size();
    left = size;
    stream.setDevice(&file);
}

NAME ESMReader::readName()
{
    NAME name;
    int sz = sizeof(NAME);
    buf.resize(sz);
    stream.readRawData(buf.data(), sz);
    memcpy(&name, buf.data(), static_cast<size_t>(sz));
    left -= sz;

    return (name >> 24 |
           ((name << 8) & 0x00FF0000) |
           ((name >> 8) & 0x0000FF00) |
           name << 24);
}

void ESMReader::notifyFailure(const QString& msg)
{
    std::ostringstream oss;
    oss << "Error: " << msg.toStdString()
        << "\nFile: " << file.fileName().toStdString()
        << "\nOffset: "
        << QString("0x%1").arg(size - left, 0, 16).toUpper().toStdString();
    throw std::runtime_error(oss.str());
}
