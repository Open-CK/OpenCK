#ifndef TES4_H
#define TES4_H

#include "records.h"

class ESMReader;

class Header
{
public:
    Header();
    void blank();
    void load(ESMReader& esm);
    void save();

private:
    RecHeader recHeader;

    // HEDR subrecord
    float version;
    qint32 numRecords;
    quint32 nextObjectID;
};

#endif // TES4_H
