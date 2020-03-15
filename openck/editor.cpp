#include "editor.hpp"

#include <QCoreApplication>
#include <QDir>

Editor::Editor(int argc, char *argv[])
{
    QString applicationName{ "OpenCK" };
    QCoreApplication::setApplicationName(applicationName);
    QCoreApplication::setOrganizationName(applicationName);

	docMed.reset(new DocumentMediator());
	connect(this, &Editor::clearFilesSignal, docMed.get(), &DocumentMediator::clearFiles);
	connect(this, &Editor::addDocumentSignal, docMed.get(), &DocumentMediator::addDocument);
	connect(this, &Editor::saveDocumentSignal, docMed.get(), &DocumentMediator::saveFile);

    viewMed.reset(new ViewMediator(*docMed.get()));
    QString dataPath{ getDataPath(applicationName) };
    viewMed->setUpDataDialog(dataPath);
    connect(viewMed.get(), &ViewMediator::addDocument, this, &Editor::addDocument);
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

void Editor::addDocument(const QStringList& files, const QString& savePath, bool isNew)
{
	emit clearFilesSignal();
    emit addDocumentSignal(files, savePath, isNew);
}

void Editor::saveDocument(const QString& path)
{
    emit saveDocumentSignal(path);
}
