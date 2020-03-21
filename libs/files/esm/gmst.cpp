#include "gmst.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

void GameSetting::load(ESMReader& esm)
{
    esm.readHeader();
    id = esm.readSubZString('EDID');

    value.load(esm, Variant::Format_GMST, id);
}

void GameSetting::save(ESMWriter& esm) const
{
    esm.writeSubZString('EDID', id);

    esm.startSubRecord('DATA');
    value.write(esm, Variant::Format_GMST);
    esm.endSubRecord();
}

void GameSetting::blank()
{
    id = "";
    value.setType(VariantType::Var_None);
}

bool operator==(const GameSetting& l, const GameSetting& r)
{
    return l.value == r.value;
}
