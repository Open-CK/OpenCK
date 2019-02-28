#ifndef FILEPATH_H
#define FILEPATH_H

#include <QDir>

struct FilePath
{
    QDir appDir;
    QDir dataDir;
    QDir programDir;

    FilePath(QString applicationName)
    {
#if defined(__WIN32) || defined(__WINDOWS__) || defined(_WIN32)
        programDir = QDir(getenv("PROGRAMFILES"));
        dataDir = QDir(programDir.path() + "/steam/steamapps/common/Skyrim/Data");
#else
        programDir = QDir(getenv("HOME"));
        dataDir = QDir(programDir.path() + "/skyrim/data");
#endif
        appDir = QDir(appDir.path() + "/" + applicationName);
    }
};

#endif //FILEPATH_H
