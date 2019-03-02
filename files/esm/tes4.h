#ifndef TES4_H
#define TES4_H

#include "records.h"

#include <QString>
#include <QVector>

class ESMReader;

enum FileFlag
{
    None = 0,
    Master = 0x01,
    Localized = 0x80,
    LightMaster = 0x200
};

struct Header
{
    Header();
    void blank();
    void load(ESMReader& esm);
    void save();

    // Header information
    RecHeader recHeader;    
    Flags flags;

    // HEDR subrecord
    float version;
    qint32 numRecords;
    quint32 nextObjectID;

    QString author;              // CNAM, optional
    QString description;         // SNAM, optional

    struct MasterData
    {
        QString name;
        quint64 size;
    };
    QVector<MasterData> masters; // MAST/DATA pairs, optional
    QVector<FormID> overrides;   // ONAM, optional

    quint32 internalVersion;     // INTV, required
    quint32 incc;                // INCC, unknown (introduced in V1.6)
};

#endif // TES4_H
