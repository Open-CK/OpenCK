#include "documentmediator.h"

DocumentMediator::DocumentMediator()
{

}

DocumentMediator::~DocumentMediator()
{

}

void DocumentMediator::addDocument(const QStringList& files, const QString& savePath, bool isNew)
{
    documents.push_back(std::make_shared<Document>(files, savePath, isNew));
}

void DocumentMediator::setPaths(const FilePaths& filePaths)
{
    paths = filePaths;
}
