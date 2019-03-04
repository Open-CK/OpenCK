#include "document.h"

Document::Document(const QStringList& files, const QString& fileSavePath, bool isNew) :
    derivedFiles(files),
    savePath(fileSavePath),
    newFile(isNew)
{

}

Document::~Document()
{

}

bool Document::isNewFile()
{
    return newFile;
}

void Document::save()
{

}

void Document::createEmpty()
{

}
