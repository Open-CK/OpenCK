#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "idcollection.hpp"
#include "metadata.hpp"
#include "../../../files/esm/esmreader.hpp"
#include "../../../files/esm/gmst.hpp"
#include "../../../files/esm/tes4.hpp"

#include <QStringList>

class Messages;

class Data
{
public:
    Data(const QStringList& files, bool isBase);

    void setMetaData(MetaData metaData);
    const MetaData& getMetaData();

	void preload(ESMReader* reader);
	bool continueLoading(Messages& messages);

	const Header& getHeader() const;
	Header& getHeader();

private:
	bool base;
    QStringList dataFiles;
    
	MetaData metaData;
	Header header;

	std::unique_ptr<ESMReader> reader;
	IdCollection<GameSetting> gameSettings;
};

#endif // WORLDDATA_H
