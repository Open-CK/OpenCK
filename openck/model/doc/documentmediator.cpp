#include "documentmediator.hpp"

#include "../../view/messageboxhelper.hpp"

DocumentMediator::DocumentMediator()
{
	loader.moveToThread(&loaderThread);
	loaderThread.start();

	connect(&loader, SIGNAL(documentLoaded(Document*)),
		this, SLOT(documentLoaded(Document*)));
	connect(&loader, SIGNAL(documentNotLoaded(Document*, const QString&)),
		this, SLOT(documentNotLoaded(Document*, const QString&)));
	connect(this, SIGNAL(loadRequest(Document*)), 
		&loader, SLOT(loadDocument(Document*)));
	connect(this, SIGNAL(cancelLoading(Document*)), 
		&loader, SLOT(abortLoading(Document*)));
	connect(&loader, SIGNAL(loadMessage(Document, const QString&)), 
		this, SIGNAL(loadMessage(Document*, const QString&)));

}

DocumentMediator::~DocumentMediator()
{
	loaderThread.quit();
	loader.stop();
	loader.hasThingsToDo().wakeAll();
	loaderThread.wait();
}

void DocumentMediator::clearFiles()
{
	documents.clear();
}

void DocumentMediator::addDocument(const QStringList& files, const QString& savePath, bool isNew)
{
	Document* document = makeDocument(files, savePath, isNew);
	insertDocument(document);
}

Document* DocumentMediator::makeDocument(const QStringList& files, const QString& savePath, bool isNew)
{
	return new Document(files, savePath, isNew);
}

void DocumentMediator::insertDocument(Document* document)
{
	documents.push_back(std::shared_ptr<Document>(document));

	emit loadRequest(document);
	loader.hasThingsToDo().wakeAll();
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

void DocumentMediator::documentLoaded(Document* document)
{

}

void DocumentMediator::documentNotLoaded(Document* document, const QString& error)
{

}
