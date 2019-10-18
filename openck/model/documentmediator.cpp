#include "documentmediator.hpp"

#include "../view/messageboxhelper.hpp"

DocumentMediator::DocumentMediator()
{
}

DocumentMediator::~DocumentMediator()
{
}

void DocumentMediator::clearFiles()
{
	documents.clear();
}

void DocumentMediator::newFile(const QStringList& files)
{
    documents.push_back(std::make_shared<Document>(files, true));
	openRelatedFiles(files);

	loadAllFiles();
}

void DocumentMediator::openFile(const QStringList& files, bool isNew, QString author, QString desc)
{
    documents.push_back(std::make_shared<Document>(files, isNew));
	openRelatedFiles(files);

	loadAllFiles();
}

void DocumentMediator::openRelatedFiles(const QStringList& files)
{
	for (const auto& file : files)
	{
		bool fileOpen = false;
		for (const auto& document : documents)
		{
			if (document->getSavePath() == file)
			{
				fileOpen = true;
			}
		}

		if (fileOpen == false)
		{
			documents.push_back(std::make_shared<Document>(QStringList(file), false));
		
			QStringList parents = documents.back()->getParentFiles();
			for (const auto& parent : parents)
			{
				bool fileOpen = false;
				for (const auto& document : documents)
				{
					if (document->getSavePath() == parent)
					{
						fileOpen = true;
					}
				}

				if (fileOpen == false)
				{
					documents.push_back(std::make_shared<Document>(QStringList(parent), false));
				}
			}
		}
	}
}

void DocumentMediator::loadAllFiles()
{
	for (auto& document : documents)
	{
		loadFile(document);
	}
}

void DocumentMediator::loadFile(std::shared_ptr<Document> document)
{
	if (!document->isNewFile())
	{
		document->load();
	}
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
