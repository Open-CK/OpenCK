#ifndef ESMESMREADER_H
#define ESMESMREADER_H

#include "esmfile.h"
#include "records.h"
#include "tes4.h"

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
    NAME swapName(NAME name);

    RecHeader readHeader();
    NAME readNSubHeader();
    QString readZString();

    bool isRecLeft();
    bool isSubLeft();

    template<typename T>
    T readType()
    {
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
