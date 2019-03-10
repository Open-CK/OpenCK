#include "gmst.h"

#include "esmreader.h"
#include "esmwriter.h"

void GameSetting::load(ESMReader& esm)
{
    esm.readHeader();

    esm.readNSubHeader();
    editorId = esm.readZString();

    esm.readNSubHeader();
    value = esm.readType<quint32>();
}

void GameSetting::save(ESMWriter& esm) const
{
    esm.startSubRecord('EDID');
    esm.writeZString(editorId);
    esm.endSubRecord();

    esm.startSubRecord('DATA');
    esm.writeType<quint32>(value.toUInt());
    esm.endSubRecord();
}

void GameSetting::blank()
{
    editorId = "";
    value = 0;
}

bool operator==(const GameSetting& l, const GameSetting& r)
{
    return l.value == r.value;
}
