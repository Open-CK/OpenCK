#ifndef ESMWRITER_H
#define ESMWRITER_H

#include "common.h"
#include "tes4.h"

#include <QDataStream>
#include <QFile>

const quint8 numRecordsPos = 28;

class ESMWriter
{
public:
    ESMWriter();
    void setVersion(float version);
    void setAuthor(const QString& author);
    void setDescription(const QString& description);
    void setNumRecords(qint32 numRecords);
    void clearMasters();
    void addMaster(QString name, quint64 size = 0);

    void save(QFile& file);

    void startRecord(NAME name, RecHeader header = RecHeader());
    void endRecord();
    void startSubRecord(NAME name);
    void endSubRecord();

    template<typename T>
    void writeType(T data)
    {
        buf.resize(sizeof(T));
        memcpy(buf.data(), &data, sizeof(T));
        stream.writeRawData(buf.data(), sizeof(T));
    }

    template<typename T>
    void writeSubData(NAME name, T data)
    {
        startSubRecord(name);

        buf.resize(sizeof(T));
        memcpy(buf.data(), &data, sizeof(T));
        stream.writeRawData(buf.data(), sizeof(T));

        endSubRecord();
    }

    void writeZString(const QString& str);
    void writeSubZString(NAME name, const QString& str);

    void close();

private:
    Header header;
    qint32 recordsWritten;
    qint64 recSizePos;
    qint64 recPos;
    qint64 subSizePos;
    qint64 subPos;

    QByteArray buf;
    QDataStream stream;
};

#endif // ESMWRITER_H
