#include "editor.h"

#include "../files/filepath.h"

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
    QSettings conf;
    conf.setDefaultFormat(QSettings::Format::IniFormat);
    FilePath paths(applicationName);

    return conf.value("data directory", paths.dataDir.path()).toString();
}
