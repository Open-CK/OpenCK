#include "document.hpp"

#include "../../files/esm/esmreader.hpp"
#include "../../files/esm/esmwriter.hpp"
#include "../view/messageboxhelper.hpp"
#include "world/metadata.hpp"

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
        preload(savePath);
    }
}

Document::~Document()
{
}

void Document::preload(const QString& fileName)
{
    ESMReader reader{ paths.dataDir.path() + "/" + fileName };

    try
    {
        reader.open();
    }
    catch (const std::runtime_error& e)
    {
        msgBoxCritical(e.what());
        return;
    }

	data.loadHeader(reader);
}

void Document::save(const QString& savePath)
{
    ESMWriter writer;

    MetaData metaData{ data.getMetaData() };
    writer.setAuthor(metaData.author);
    writer.setDescription(metaData.description);

    QFile saveFile{ savePath };
    if (saveFile.open(QIODevice::WriteOnly))
    {
        writer.save(saveFile);
    }
}

void Document::setAuthor(const QString& author)
{
    MetaData metaData = data.getMetaData();
    metaData.author = author;
    data.setMetaData(metaData);
}

void Document::setDescription(const QString& desc)
{
    MetaData metaData = data.getMetaData();
    metaData.description = desc;
    data.setMetaData(metaData);
}

void Document::createBase()
{
    MetaData blankMetaData;
    blankMetaData.blank();
    data.setMetaData(blankMetaData);
}

bool Document::isNewFile() const
{
    return newFile;
}

const QString Document::getSavePath() const
{
	return savePath;
}

QStringList Document::getDerivedFiles() const
{
	return derivedFiles;
}

QStringList Document::getParentFiles() const
{
	const Header header = data.getHeader();
	QStringList list;
	
	for (const auto& master : header.masters)
	{
		list.append(master.name);
	}

	return list;
}
