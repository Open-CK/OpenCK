#include "document.h"

#include "../../files/esm/esmreader.h"
#include "../../files/esm/esmwriter.h"

Document::Document(const QStringList& files, bool isNew) :
    derivedFiles(files),
    newFile(isNew)
{
    if (newFile)
    {
        savePath = "";
        createBase();
    }
    else
    {
        savePath = derivedFiles.last();
        load(savePath);
    }
}

Document::~Document()
{

}

void Document::load(const QString& fileName)
{

}

void Document::save()
{

}

void Document::createBase()
{

}

bool Document::isNewFile()
{
    return newFile;
}
