#include "document.hpp"

#include "../../view/messageboxhelper.hpp"
#include "../world/metadata.hpp"

#include <QCoreApplication>
#include <QFile>

Document::Document(const QStringList& files, bool isNew, bool isBase) :
    paths(FilePaths(QCoreApplication::applicationName())),
    derivedFiles(files),
    newFile(isNew),
	base(isBase),
    data(files, isBase)
{   
    if (newFile)
    {
        savePath = "";
        createNew();
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
	reader = std::make_unique<ESMReader>(paths.dataDir.path() + "/" + fileName);

    try
    {
        reader->open();
    }
    catch (const std::runtime_error& e)
    {
        msgBoxCritical(e.what());
        return;
    }

	data.preload(*reader);
}

void Document::load()
{
	data.continueLoading(*reader);
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

void Document::createNew()
{
    MetaData blankMetaData;
    blankMetaData.blank();
    data.setMetaData(blankMetaData);
}

bool Document::isNewFile() const
{
    return newFile;
}

bool Document::isBase() const
{
	return base;
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
