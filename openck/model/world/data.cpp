#include "data.h"

Data::Data(const QStringList& files)
    : dataFiles(files)
{

}

void Data::setMetaData(const MetaData& inMetaData)
{
    metaData = inMetaData;
}
