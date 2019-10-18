#include "data.hpp"
#include "../../../files/esm/esmreader.hpp"

#include <QDebug>

Data::Data(const QStringList& files, bool isBase)
    : dataFiles(files), base(isBase)
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
		case 'GRUP': reader.skipGrupHeader();			break;
		case 'GMST': gameSettings.load(reader, base);	break;
		default:
		{
			std::string s(reinterpret_cast<const char*>(&(name)), sizeof(NAME));
			std::reverse(s.begin(), s.end());
			qDebug() << "Unknown record:" 
					 << s.c_str();
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
