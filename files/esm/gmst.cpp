#include "gmst.h"

#include "esmreader.h"
#include "esmwriter.h"

void GameSetting::load(ESMReader& esm)
{
    esm.readHeader();
    editorId = esm.readSubZString('EDID');
    value = esm.readSubData<quint32>('DATA');
}

void GameSetting::save(ESMWriter& esm) const
{
    esm.writeSubZString('EDID', editorId);
    esm.writeSubData<quint32>('DATA', value.toUInt());
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
