#include "data.hpp"

Data::Data(const QStringList& files)
    : dataFiles(files)
{

}

void Data::setMetaData(MetaData inMetaData)
{
    metaData = inMetaData;
}

const MetaData& Data::getMetaData()
{
    return metaData;
}
