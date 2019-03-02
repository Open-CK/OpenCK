#include "tes4.h"

#include "esmreader.h"

#include <QDebug>

Header::Header()
    : author(""),
      description("")
{

}

void Header::blank()
{
    recHeader = RecHeader();
}

void Header::load(ESMReader& esm)
{
    recHeader = esm.readHeader();

    while (esm.isRecLeft())
    {
        NAME subName = esm.readNSubHeader();
        switch (subName)
        {
        case 'HEDR':
        {
            version = esm.readType<float>();
            numRecords = esm.readType<qint32>();
            nextObjectID = esm.readType<quint32>();
            break;
        }
        case 'CNAM':
        {
            author = esm.readZString();
            break;
        }
        case 'SNAM':
        {
            description = esm.readZString();
            break;
        }
        case 'MAST':
        {
            MasterData mst;
            mst.name= esm.readZString();

            // DATA subrecord will follow
            esm.readNSubHeader();
            mst.size = esm.readType<quint64>();
            masters.push_back(mst);
            break;
        }
        case 'ONAM':
        {
            while (esm.isSubLeft())
            {
                overrides.push_back(esm.readType<FormID>());
            }
            break;
        }
        case 'INTV':
        {
            internalVersion = esm.readType<quint32>();
            break;
        }
        case 'INCC':
        {
            incc = esm.readType<quint32>();
            break;
        }
        }
    }
}

void Header::save()
{

}
