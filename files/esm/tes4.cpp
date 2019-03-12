#include "tes4.h"

#include "esmreader.h"
#include "esmwriter.h"

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
    flags.val = recHeader.flags.val;

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

void Header::save(ESMWriter& esm)
{
    esm.startSubRecord('HEDR');
    esm.writeType<float>(version);
    esm.writeType<qint32>(numRecords);
    esm.writeType<quint32>(nextObjectID);
    esm.endSubRecord();

    if (author.compare("") != 0)
    {
        esm.writeSubZString('CNAM', author);
    }

    if (description.compare("") != 0)
    {
        esm.writeSubZString('SNAM', description);
    }

    if (!masters.empty())
    {
        for (auto master: masters)
        {
            esm.writeSubZString('MAST', master.name);
            esm.writeSubData<quint64>('DATA', master.size);
        }
    }

    if (!overrides.empty())
    {
        esm.startSubRecord('ONAM');

        for (auto override: overrides)
        {
            esm.writeType<FormID>(override);
        }

        esm.endSubRecord();
    }

    esm.writeSubData<quint32>('INTV', internalVersion);

    if (incc != 0)
    {
        esm.writeSubData<quint32>('INCC', incc);
    }
}
