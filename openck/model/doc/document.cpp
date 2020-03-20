#include "document.hpp"

#include "../doc/messages.hpp"
#include "../world/metadata.hpp"
#include "../../view/messageboxhelper.hpp"

#include <QCoreApplication>
#include <QFile>

Document::Document(const QStringList& contentFiles, const QString& savePath, bool isNew) :
    paths(FilePaths(QCoreApplication::applicationName())),
    contentFiles(contentFiles),
    newFile(isNew),
    data(contentFiles, paths)
{   
    if (newFile)
    {
        if (contentFiles.size() == 1)
        {
            createNew();
        }
    }

    reports.reset(new ReportModel());
}

Document::~Document()
{
}

void Document::save(const QString& savePath)
{
    ESMWriter writer;

    QFile saveFile{ savePath };
    if (saveFile.open(QIODevice::WriteOnly))
    {
        writer.save(saveFile);
    }
}

void Document::createNew()
{

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

QStringList Document::getContentFiles() const
{
    return contentFiles;
}

std::shared_ptr<ReportModel> Document::getReport()
{
    return reports;
}

const Data& Document::getData() const
{
    return data;
}

Data& Document::getData()
{
    return data;
}
