#ifndef RECORDS_H
#define RECORDS_H

#include <QtGlobal>

typedef quint32 FormID;

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

    RecHeader()
        : size(0),
          flags(0),
          id(0),
          vcDay(0),
          vcMonth(0),
          vcLastUser(0),
          vcCurrUser(0),
          version(0),
          unknown(0)
    {

    }
};

#endif // RECORDS_H
