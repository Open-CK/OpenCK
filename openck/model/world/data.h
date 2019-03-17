#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "collection.h"
#include "metadata.h"

#include <QStringList>

class ESMReader;

class Data
{
public:
    Data(const QStringList& files);

    void setMetaData(MetaData metaData);
    const MetaData& getMetaData();

private:
    QStringList dataFiles;

    MetaData metaData;
};

#endif // WORLDDATA_H
