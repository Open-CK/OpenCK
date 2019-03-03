#include "records.h"

#include "esmwriter.h"

RecHeader::RecHeader()
    : size(0),
      flags(0),
      id(0),
      vcDay(0),
      vcMonth(0),
      vcLastUser(0),
      vcCurrUser(0),
      version(0),
      unknown(0)
{

}

void RecHeader::save(ESMWriter& esm, NAME name)
{
    esm.writeType<NAME>(name);
    esm.writeType<quint32>(size);
    esm.writeType<quint32>(flags);
    esm.writeType<quint32>(id);
    esm.writeType<quint8>(vcDay);
    esm.writeType<quint8>(vcMonth);
    esm.writeType<quint8>(vcLastUser);
    esm.writeType<quint8>(vcCurrUser);
    esm.writeType<quint16>(version);
    esm.writeType<quint16>(unknown);
}
