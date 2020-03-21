#ifndef ESMFILE_H
#define ESMFILE_H

#include "common.hpp"
#include "../data/strings.hpp"

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
    qint64 recCount;

    Strings strings;
    bool localised;

    ESMFile(QString fileName)
        : file(fileName),
          recLeft(0),
          localised(false)
    {
        size = file.size();
        left = file.size();
    }

    ESMFile(QString fileName, const FilePaths& filePaths)
        : file(fileName),
          localised(false)
    {
        strings.load(fileName, filePaths);

        size = file.size();
        left = file.size();
    }

    void forward(qint64 offset, bool recHeader = false)
    {
        left -= offset;
        
        if (!recHeader)
        {
            recLeft -= offset;
            subLeft -= offset;
        }
    }
};

#endif // ESMFILE_H
