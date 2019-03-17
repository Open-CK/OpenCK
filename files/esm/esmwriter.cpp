#include "esmwriter.h"

#include "common.h"

ESMWriter::ESMWriter()
{
    header.blank();
}

void ESMWriter::setVersion(float version)
{
    header.version = version;
}

void ESMWriter::setAuthor(const QString& author)
{
    header.author = author;
}

void ESMWriter::setDescription(const QString& description)
{
    header.description = description;
}

void ESMWriter::setNumRecords(qint32 numRecords)
{
    header.numRecords = numRecords;
}

void ESMWriter::clearMasters()
{
    header.masters.clear();
}

void ESMWriter::addMaster(QString name, quint64 size)
{
    MasterData master{ name, size };
    header.masters.push_back(master);
}

void ESMWriter::save(QFile& file)
{
    stream.setDevice(&file);
    recordsWritten = 0;

    startRecord('TES4');
    header.save(*this);
    endRecord();
}

void ESMWriter::startRecord(NAME name, RecHeader header)
{
    recordsWritten++;
    recSizePos = stream.device()->pos() + static_cast<qint64>(sizeof(NAME));
    header.save(*this, swapName(name));
    recPos = stream.device()->pos();
}

void ESMWriter::endRecord()
{
    qint64 currentPos{ stream.device()->pos() };
    stream.device()->seek(recSizePos);
    writeType<quint32>(static_cast<quint32>(currentPos - recPos));
    stream.device()->seek(currentPos);
}

void ESMWriter::startSubRecord(NAME name)
{
    writeType<NAME>(swapName(name));
    subSizePos = stream.device()->pos();
    writeType<quint16>(0);
    subPos = stream.device()->pos();
}

void ESMWriter::endSubRecord()
{
    qint64 currentPos{ stream.device()->pos() };
    stream.device()->seek(subSizePos);
    writeType<quint16>(static_cast<quint16>(currentPos - subPos));
    stream.device()->seek(currentPos);
}

void ESMWriter::writeZString(const QString& str)
{
    qint32 size{ str.size() + 1 };
    buf.resize(size);
    buf.fill('\0', size);
    QByteArray bytes{ str.toUtf8() };
    bytes.push_back('\0');
    stream.writeRawData(bytes.data(), size);
}

void ESMWriter::writeSubZString(NAME name, const QString &str)
{
    startSubRecord(name);
    writeZString(str);
    endSubRecord();
}

void ESMWriter::close()
{
    // Do not include TES4 record in numRecords
    stream.device()->seek(numRecordsPos);
    writeType<quint32>(static_cast<quint32>(recordsWritten - 1));
}
