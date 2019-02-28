#include "editor.h"

#include "../files/filepath.h"

#include <QCoreApplication>
#include <QDir>

Editor::Editor(int argc, char *argv[])
{
    QString applicationName = "OpenCK";
    QCoreApplication::setApplicationName(applicationName);
    QCoreApplication::setOrganizationName(applicationName);

    QSettings conf;
    conf.setDefaultFormat(QSettings::Format::IniFormat);
    FilePath paths(applicationName);
    QDir dataDir(conf.value("data directory", paths.dataDir.path()).toString());

    viewMed.reset(new ViewMediator());
}

Editor::~Editor()
{

}
