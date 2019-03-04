#include "editor.h"

#include <QCoreApplication>
#include <QDir>

Editor::Editor(int argc, char *argv[])
{
    QString applicationName{ "OpenCK" };
    QCoreApplication::setApplicationName(applicationName);
    QCoreApplication::setOrganizationName(applicationName);

    viewMed.reset(new ViewMediator());
    QString dataPath{ getDataPath(applicationName) };
    viewMed->setUpDataDialog(dataPath);
}

Editor::~Editor()
{

}

QString Editor::getDataPath(const QString& applicationName)
{
    FilePaths paths{ applicationName };
    QSettings conf{ paths.configPath, QSettings::IniFormat };

    conf.beginGroup(applicationName);
    QString dataPath{ conf.value("DataDirectory", paths.dataDir.path()).toString() };
    conf.endGroup();

    return dataPath;
}
