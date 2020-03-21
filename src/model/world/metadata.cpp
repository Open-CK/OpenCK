#include "metadata.hpp"

#include "../../../libs/files/esm/esmreader.hpp"
#include "../../../libs/files/esm/esmwriter.hpp"

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
