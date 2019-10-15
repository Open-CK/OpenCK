#include "documentmediator.hpp"

#include "../view/messageboxhelper.hpp"

DocumentMediator::DocumentMediator()
{
}

DocumentMediator::~DocumentMediator()
{
}

void DocumentMediator::clearFiles()
{
	documents.clear();
}

void DocumentMediator::newFile(const QStringList& files)
{
    documents.push_back(std::make_shared<Document>(files, true));

	QStringList parents = documents.back()->getDerivedFiles();
	for (auto parent : parents) 
	{
		openFile(QStringList(parent), false);
	}
}

void DocumentMediator::openFile(const QStringList& files, bool isNew, QString author, QString desc)
{
    documents.push_back(std::make_shared<Document>(files, isNew));
}

void DocumentMediator::saveFile(const QString& path)
{
    if (documents.empty())
    {
        msgBoxCritical("No file open, cannot save.");
    }
    else
    {
        documents.back().get()->save(path);
    }
}

void DocumentMediator::setPaths(const FilePaths& filePaths)
{
    paths = filePaths;
}
