#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "idcollection.hpp"
#include "metadata.hpp"
#include "../../../files/filepaths.hpp"
#include "../../../files/esm/esmreader.hpp"
#include "../../../files/esm/gmst.hpp"
#include "../../../files/esm/tes4.hpp"

#include <QStringList>

class Messages;

class Data
{
public:
    Data(const QStringList& files, const FilePaths& paths);

	int preload(const QString& filename, bool base);
	bool continueLoading(Messages& messages);

private:
	std::unique_ptr<ESMReader> reader;

    QStringList contentFiles;
	FilePaths paths;
	bool base;
	
	IdCollection<GameSetting> gameSettings;
	Collection<MetaData> metaData;
};

#endif // WORLDDATA_H
