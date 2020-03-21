#ifndef LCRT_H
#define LCRT_H

class ESMReader;
class ESMWriter;

#include "common.hpp"

#include <QString>

struct LocationRefType
{
    QString id;
    Color color;

    void load(ESMReader& esm);
    void save(ESMWriter& esm) const;
    void blank();
};

bool operator==(const LocationRefType& l, const LocationRefType& r);

#endif // LCRT_H
