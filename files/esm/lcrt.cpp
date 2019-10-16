#include "lcrt.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"

void LocationRefType::load(ESMReader& esm)
{
    esm.readHeader();
    editorId = esm.readSubZString('EDID');
    color = esm.readSubData<Color>('CNAM');
}

void LocationRefType::save(ESMWriter& esm) const
{
    esm.writeSubZString('EDID', editorId);
    esm.writeSubData<Color>('CNAM', color);
}

void LocationRefType::blank()
{
    editorId = "";
    color = 0;
}

bool operator==(const LocationRefType& l, const LocationRefType& r)
{
    return l.color == r.color;
}
