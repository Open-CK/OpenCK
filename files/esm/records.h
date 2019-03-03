#ifndef RECORDS_H
#define RECORDS_H

#include "common.h"

#include <QtGlobal>

typedef quint32 FormID;

class ESMWriter;

struct Flags
{
    quint32 val;

    inline bool test(quint32 flag) const
    {
        return val & flag;
    }
};

struct RecHeader
{
    quint32 size;
    quint32 flags;
    quint32 id;
    quint8 vcDay;
    quint8 vcMonth;
    quint8 vcLastUser;
    quint8 vcCurrUser;
    quint16 version;
    quint16 unknown;

    RecHeader();

    void save(ESMWriter& esm, NAME name);
};

#endif // RECORDS_H
