#ifndef FILEPATH_H
#define FILEPATH_H

#include <QCoreApplication>
#include <QDir>

const QString iniName = "editor.ini";

struct FilePath
{
    QDir appDir;
    QDir dataDir;
    QDir programDir;

    QString configPath;

    FilePath(QString applicationName)
    {
        programDir = QCoreApplication::applicationDirPath();
        configPath = programDir.path() + "/" + iniName;

#if defined(__WIN32) || defined(__WINDOWS__) || defined(_WIN32)        
        dataDir = QDir(programDir.path() + "/steam/steamapps/common/Skyrim/Data");
#else
        dataDir = QDir(programDir.path() + "/skyrim/data");
#endif
        appDir = QDir(programDir.path() + "/" + applicationName);
    }
};

#endif //FILEPATH_H
