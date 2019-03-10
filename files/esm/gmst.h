#ifndef GMST_H
#define GMST_H

class ESMReader;
class ESMWriter;

#include <QString>
#include <QVariant>

struct GameSetting
{
    QString editorId;
    QVariant value;

    void load(ESMReader& esm);
    void save(ESMWriter& esm) const;
    void blank();
};

bool operator==(const GameSetting& l, const GameSetting& r);

#endif // GMST_H
