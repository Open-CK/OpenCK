#include "data.hpp"

#include "../doc/messages.hpp"
#include "../world/ckid.hpp"
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

void Data::preload(ESMReader* reader_)
{
	reader.reset(reader_);

	header = reader->getHeader();
	metaData.author = header.author;
	metaData.description = header.description;
}

bool Data::continueLoading(Messages& messages)
{
	if (!reader->isLeft())
	{
		return true;
	}
	else
	{
		NAME name = reader->readName();

		switch (name)
		{
		case 'GRUP': reader->skipGrupHeader();			break;
		case 'GMST': gameSettings.load(*reader, base);	break;
		default:
		{
			messages.append(CkId::Type_LoadingLog, "Unknown record encountered!");
			reader->skipRecord();
			break;
		}
		}

		return false;
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
