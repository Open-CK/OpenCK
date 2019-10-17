#ifndef ESMESMREADER_H
#define ESMESMREADER_H

#include "esmfile.hpp"
#include "records.hpp"
#include "tes4.hpp"

#include <QDataStream>
#include <QFile>
#include <QString>

class ESMReader
{
public:
    ESMReader(const QString& path);
    ~ESMReader();

    void open();
    void startStream();

    NAME readName();
    bool isNextName(NAME name);
    RecHeader readHeader();
    NAME readNSubHeader();
    QString readZString();
    QString readSubZString(NAME name);

    bool isRecLeft();
    bool isSubLeft();

    const Header& getHeader() const;
	Header getHeader();

    template<typename T>
    inline T readType()
    {
        T data;
        buf.resize(sizeof(T));
        stream.readRawData(buf.data(), sizeof(T));
        memcpy(&data, buf.data(), sizeof(T));
        esm.forward(sizeof(T));
        return data;
    }

    template<typename T>
    T readSubData(NAME expectedName)
    {
        NAME actualName = readNSubHeader();

        if (actualName != expectedName)
        {
            throw std::runtime_error("Error process subrecord - unexpected name.");
        }

        T data;
        buf.resize(sizeof(T));
        stream.readRawData(buf.data(), sizeof(T));
        memcpy(&data, buf.data(), sizeof(T));
        esm.forward(sizeof(T));
        return data;
    }

private:
    [[noreturn]] void notifyFailure(const QString& msg);

    ESMFile esm;
    QDataStream stream;
    QByteArray buf;

    Header header;
};

#endif // ESMESMREADER_H
