#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "idcollection.hpp"
#include "metadata.hpp"

#include "../../../files/esm/gmst.hpp"
#include "../../../files/esm/tes4.hpp"

#include <QStringList>

class ESMReader;

class Data
{
public:
    Data(const QStringList& files);

    void setMetaData(MetaData metaData);
    const MetaData& getMetaData();

	void preload(ESMReader& reader);
	void continueLoading(ESMReader& reader);

	const Header& getHeader() const;
	Header& getHeader();

private:
	bool base;
    QStringList dataFiles;
    
	MetaData metaData;
	Header header;

	IdCollection<GameSetting> gameSettings;
};

#endif // WORLDDATA_H
