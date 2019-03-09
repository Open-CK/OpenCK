#include "metadata.h"

#include "../../../files/esm/esmreader.h"
#include "../../../files/esm/esmwriter.h"

void MetaData::blank()
{
    author.clear();
    description.clear();
}

void MetaData::load(ESMReader& esm)
{
    author = esm.getHeader().author;
    description = esm.getHeader().description;
}

void MetaData::save(ESMWriter& esm) const
{
    esm.setAuthor(author);
    esm.setDescription(description);
}
