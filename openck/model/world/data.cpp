#include "data.hpp"
#include "../../../files/esm/esmreader.hpp"

#include <QDebug>

Data::Data(const QStringList& files)
    : dataFiles(files), base(false)
{
	header.blank();
}

void Data::setMetaData(MetaData inMetaData)
{
    metaData = inMetaData;
}

const MetaData& Data::getMetaData()
{
    return metaData;
}

void Data::preload(ESMReader& reader)
{
	header = reader.getHeader();
	metaData.author = header.author;
	metaData.description = header.description;
}

void Data::continueLoading(ESMReader& reader)
{
	while (reader.isLeft())
	{
		NAME name = reader.readName();

		switch (name)
		{
		case 'GRUP':
			reader.skipGrupHeader();
			break;
		case 'GMST':
			gameSettings.load(reader, base);
			break;
		default:
		{
			qDebug() << "Unknown record: ";
			qDebug() << reinterpret_cast<const char*>(&(name));
			reader.skipRecord();
			break;
		}
		}
	}
}

const Header& Data::getHeader() const
{
	return header;
}

Header& Data::getHeader()
{
	return header;
}
