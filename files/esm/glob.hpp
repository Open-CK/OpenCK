#ifndef GLOB_H
#define GLOB_H

class ESMReader;
class ESMWriter;

#include "variant.hpp"

#include <QString>
#include <QVariant>

struct GlobalVariable
{
    enum Flag
    {
        None = 0,
        Constant = 0x40
    };

    QString id;
    Variant value;

    void load(ESMReader& esm);
    void save(ESMWriter& esm) const;
    void blank();

    bool constant;
};

bool operator==(const GlobalVariable& l, const GlobalVariable& r);

#endif // GLOB_H
