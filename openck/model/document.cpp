#include "document.h"

#include "../../files/esm/esmreader.h"
#include "../../files/esm/esmwriter.h"
#include "world/metadata.h"

#include <QCoreApplication>
#include <QFile>

Document::Document(const QStringList& files, bool isNew) :
    paths(FilePaths(QCoreApplication::applicationName())),
    derivedFiles(files),
    newFile(isNew),
    data(files)
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
    ESMReader reader{ paths.dataDir.path() + "/" + fileName };
    reader.open();

    MetaData metaData;
    metaData.load(reader);
}

void Document::save(const QString& savePath)
{
    ESMWriter writer;

    MetaData metaData{ data.getMetaData() };
    writer.setAuthor(metaData.author);
    writer.setDescription(metaData.description);

    QFile saveFile{ savePath };
    writer.save(saveFile);
}

void Document::createBase()
{
    MetaData blankMetaData;
    blankMetaData.blank();
    data.setMetaData(blankMetaData);
}

bool Document::isNewFile()
{
    return newFile;
}
