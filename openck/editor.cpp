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
    connect(viewMed.get(), &ViewMediator::newDocument, this, &Editor::newDocument);
    connect(viewMed.get(), &ViewMediator::openDocument, this, &Editor::openDocument);
    connect(viewMed.get(), &ViewMediator::saveDocument, this, &Editor::saveDocument);

    docMed.reset(new DocumentMediator());
    connect(this, &Editor::newDocumentSignal, docMed.get(), &DocumentMediator::newFile);
    connect(this, &Editor::openDocumentSignal, docMed.get(), &DocumentMediator::openFile);
    connect(this, &Editor::saveDocumentSignal, docMed.get(), &DocumentMediator::saveFile);
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

void Editor::newDocument(const QStringList& files)
{
    emit newDocumentSignal(files);
}

void Editor::openDocument(const QStringList& files, bool isNew)
{
    emit openDocumentSignal(files, isNew);
}

void Editor::saveDocument(const QString& path)
{
    emit saveDocumentSignal(path);
}
