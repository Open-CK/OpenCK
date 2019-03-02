#ifndef ESMESMREADER_H
#define ESMESMREADER_H

#include <QDataStream>
#include <QFile>
#include <QString>

typedef uint32_t NAME;

class ESMReader
{
public:
    ESMReader(const QString& path, const QString& name);
    ~ESMReader();

    void open();
    void startStream();

    NAME readName();

private:
    void notifyFailure(const QString& msg);

    QFile file;
    QString fileName;
    QDataStream stream;
    QByteArray buf;
    qint64 size;
    qint64 left;
};

#endif // ESMESMREADER_H
