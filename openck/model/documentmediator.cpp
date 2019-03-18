#include "documentmediator.hpp"

#include "../view/messageboxhelper.hpp"

DocumentMediator::DocumentMediator()
{
}

DocumentMediator::~DocumentMediator()
{
}

void DocumentMediator::newFile(const QStringList& files, QString author, QString desc)
{
    documents.push_back(std::make_shared<Document>(files, true));
    documents.back()->setAuthor(author);
    documents.back()->setDescription(desc);
}

void DocumentMediator::openFile(const QStringList& files, bool isNew, QString author, QString desc)
{
    documents.push_back(std::make_shared<Document>(files, isNew));
    documents.back()->setAuthor(author);
    documents.back()->setDescription(desc);
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
