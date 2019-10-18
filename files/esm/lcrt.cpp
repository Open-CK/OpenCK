#include "lcrt.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

void LocationRefType::load(ESMReader& esm)
{
    esm.readHeader();
    id = esm.readSubZString('EDID');
    color = esm.readSubData<Color>('CNAM');
}

void LocationRefType::save(ESMWriter& esm) const
{
    esm.writeSubZString('EDID', id);
    esm.writeSubData<Color>('CNAM', color);
}

void LocationRefType::blank()
{
    id = "";
    color = 0;
}

bool operator==(const LocationRefType& l, const LocationRefType& r)
{
    return l.color == r.color;
}
