#include "esmreader.hpp"

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

    if (!esm.file.open(QIODevice::ReadOnly))
    {
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

void ESMReader::skipGrupHeader()
{
	readType<quint32>(true);	// size
	readType<quint32>(true);	// label
	readType<quint32>(true);	// group type
	readType<quint8>(true);		// vc day
	readType<quint8>(true);		// vc month
	readType<quint8>(true);		// recent user
	readType<quint8>(true);		// current user
	readType<quint32>(true);	// unknown
}

RecHeader ESMReader::readHeader()
{
    RecHeader header;
    header.size = readType<quint32>(true);
    esm.recLeft = header.size;
    esm.subLeft = 0;

    header.flags.val = readType<quint32>(true);
    header.id = readType<quint32>(true);
    header.vcDay = readType<quint8>(true);
    header.vcMonth = readType<quint8>(true);
	header.vcLastUser = readType<quint8>(true);
    header.vcCurrUser = readType<quint8>(true);
    header.version = readType<quint16>(true);
    header.unknown = readType<quint16>(true);

    return header;
}

NAME ESMReader::readNSubHeader()
{
    NAME name{ readName() };
    quint16 sz = readType<quint16>();
    esm.subLeft = sz;

    return name;
}

quint16 ESMReader::readSubHeader()
{
	quint16 sz = readType<quint16>();
	esm.subLeft = sz;

	return sz;
}

QString ESMReader::readZString()
{
	const quint16 sz = static_cast<quint16>(esm.subLeft);
	buf.resize(sz);
	stream.readRawData(buf.data(), sz);
	esm.forward(sz);
	return QString(QByteArray(buf));
}

QString ESMReader::readSubZString(NAME expectedName)
{
	NAME actualName = readNSubHeader();

	if (actualName != expectedName)
	{
		throw std::runtime_error("Error process subrecord - unexpected name.");
	}

	return readZString();
}

bool ESMReader::isLeft()
{
	return esm.left > 0;
}

bool ESMReader::isRecLeft()
{
    return esm.recLeft > 0;
}

bool ESMReader::isSubLeft()
{
    return esm.subLeft > 0;
}

void ESMReader::skipRecord()
{
	readHeader();
	skip(esm.recLeft);
}

void ESMReader::skipSub()
{
	readSubHeader();
	skip(esm.subLeft);
}

void ESMReader::skip(int bytes)
{
	esm.forward(bytes);
	esm.file.seek(esm.file.pos() + bytes);
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

const Header& ESMReader::getHeader() const
{
    return header;
}

Header ESMReader::getHeader()
{
	return header;
}
