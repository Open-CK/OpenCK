#ifndef FILEPATH_H
#define FILEPATH_H

#include <QCoreApplication>
#include <QDir>

const QString iniName = "editor.ini";

struct FilePaths
{
    QDir appDir;
    QDir dataDir;
    QDir programDir;

    QString appPath;
    QString configPath;

    FilePaths()
    {
    }

    FilePaths(QString applicationName)
    {
        appDir = QCoreApplication::applicationDirPath();
        configPath = appDir.path() + "/" + iniName;
        appDir = QDir(programDir.path() + "/" + applicationName);

#if defined(__WIN32) || defined(__WINDOWS__) || defined(_WIN32)        
        dataDir = QDir(QString(getenv("PROGRAMFILES(X86)")) + "/Steam/steamapps/common/Skyrim/Data");
#else
        dataDir = QDir(QString(getenv("HOME")) + "/skyrim/data");
#endif
    }
};

#endif //FILEPATH_H
