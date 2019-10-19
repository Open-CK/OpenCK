#include "loader.hpp"

#include "document.hpp"
#include "documentstate.hpp"
#include "messages.hpp"
#include "../tools/reports.hpp"

#include <iostream>
#include <stdexcept>

Loader::Stage::Stage() :
	file(0), recordsLoaded(0), recordsLeft(false)
{
}

Loader::Loader() :
	shouldStop(false)
{
	timer = std::make_unique<QTimer>(this);

	connect(timer.get(), SIGNAL(timeout()), this, SLOT(load()));
	timer->start();
}

QWaitCondition& Loader::hasThingsToDo()
{
	return toDo;
}

void Loader::stop()
{
	shouldStop = true;
}

void Loader::load()
{
	if (documents.empty())
	{
		mutex.lock();
		toDo.wait(&mutex);
		mutex.unlock();

		if (shouldStop)
		{
			timer->stop();
		}

		return;
	}

	auto it = documents.begin();
	Document* document = it->first;

	int index = static_cast<int>(document->getDerivedFiles().size()) - 1;
	bool done = false;

	try
	{
		if (it->second.recordsLeft)
		{
			Messages messages(Message::Error);
			const int batchSize = 50;

			for (int i = 0; i < batchSize; i++)
			{
				if (document->getData().continueLoading(messages))
				{
					it->second.recordsLeft = false;
					break;
				}
				else
				{
					++(it->second.recordsLoaded);
				}
			}

			CkId log(CkId::Type_LoadingLog, 0);

			for (Messages::Iterator messageIt = messages.begin(); messageIt != messages.end(); ++messageIt)
			{
				document->getReport()->add(*messageIt);
				emit loadMessage(document, messageIt->message);
			}

			emit nextRecordGroup(document, it->second.recordsLoaded);

			return;
		}
	}
	catch (const std::exception& e)
	{
		documents.erase(it);
		emit documentNotLoaded(document, e.what());
		return;
	}

	if (done)
	{
		documents.erase(it);
		emit documentLoaded(document);
	}
}

void Loader::loadDocument(Document* document)
{
	documents.push_back(QPair<Document*, Stage>(document, Stage()));
}

void Loader::abortLoading(Document* document)
{
	for (auto it = documents.begin(); it != documents.end(); ++it)
	{
		if (it->first == document)
		{
			documents.erase(it);
			emit documentNotLoaded(document, "");
			break;
		}
	}
}