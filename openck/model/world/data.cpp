#include "data.hpp"

#include "../doc/messages.hpp"
#include "../world/ckid.hpp"
#include "../../../files/esm/esmreader.hpp"

#include <QDebug>

Data::Data(const QStringList& files, const FilePaths& paths)
    : contentFiles(files), paths(paths)
{
}

int Data::preload(const QString& filename, bool base_)
{
	reader.reset(new ESMReader(paths.dataDir.path() + "/" + filename));
	reader->open();
	base = base_;

	if (!base)
	{
		MetaData metaData_;
		metaData_.id = "esm::metadata";
		metaData_.load(*reader);

		metaData.appendRecord(Record<MetaData>(State::State_ModifiedOnly, 0, &metaData_));
	}

	return reader->recordCount();
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
