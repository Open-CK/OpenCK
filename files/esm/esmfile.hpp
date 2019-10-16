#ifndef ESMFILE_H
#define ESMFILE_H

#include "common.h"

#include <QFile>

struct ESMFile
{
    QFile file;
    NAME currRecord;
    NAME currSubRecord;
    qint64 size;
    qint64 left;
    qint64 recLeft;
    qint64 subLeft;

    ESMFile(QString fileName)
        : file(fileName),
          recLeft(0)
    {
		size = file.size();
        left = file.size();
    }

    void forward(qint64 offset)
    {
        left -= offset;
        recLeft -= offset;
        subLeft -= offset;
    }
};

#endif // ESMFILE_H
