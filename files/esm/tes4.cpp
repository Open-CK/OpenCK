#include "tes4.h"

#include "esmreader.h"

#include <QDebug>

Header::Header()
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
        }
        }
    }
}

void Header::save()
{

}
