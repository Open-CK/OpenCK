#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "collection.hpp"
#include "metadata.hpp"

#include "../../../files/esm/tes4.hpp"

#include <QStringList>

class ESMReader;

class Data
{
public:
    Data(const QStringList& files);

    void setMetaData(MetaData metaData);
    const MetaData& getMetaData();

	void loadHeader(ESMReader& reader);

	const Header& getHeader() const;
	Header& getHeader();

private:
    QStringList dataFiles;
    
	MetaData metaData;
	Header header;
};

#endif // WORLDDATA_H
