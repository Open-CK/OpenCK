#include "data.hpp"
#include "../../../files/esm/esmreader.hpp"

Data::Data(const QStringList& files)
    : dataFiles(files)
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

void Data::loadHeader(ESMReader& reader)
{
	header = reader.getHeader();
	metaData.author = header.author;
	metaData.description = header.description;
}

const Header& Data::getHeader() const
{
	return header;
}

Header& Data::getHeader()
{
	return header;
}
