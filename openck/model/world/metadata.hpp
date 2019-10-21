#ifndef METADATA_H
#define METADATA_H

#include <QString>

class ESMReader;
class ESMWriter;

struct MetaData
{
	QString id;
    QString author;
    QString description;

    void blank();

    void load(ESMReader& esm);
    void save(ESMWriter& esm) const;
};

#endif // METADATA_H
