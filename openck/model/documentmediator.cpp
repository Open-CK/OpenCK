#include "documentmediator.h"

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

void DocumentMediator::setPaths(const FilePaths& filePaths)
{
    paths = filePaths;
}
