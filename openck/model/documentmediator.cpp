#include "documentmediator.h"

#include "../view/messageboxhelper.h"

DocumentMediator::DocumentMediator()
{
}

DocumentMediator::~DocumentMediator()
{
}

void DocumentMediator::newFile(const QStringList& files)
{
    documents.push_back(std::make_shared<Document>(files, true));
}

void DocumentMediator::openFile(const QStringList& files, bool isNew)
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
