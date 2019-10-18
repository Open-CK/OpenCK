#ifndef COLLECTION_H
#define COLLECTION_H

#include "basecollection.hpp"
#include "record.hpp"

#include <QMap>
#include <QVector>

const int NOT_FOUND = -1;

template<typename ESXRecordT>
struct IdAccessor
{
	void setId(ESXRecordT& record, const QString& id) const;
	QString getId(const ESXRecordT& record) const;
};

template<typename ESXRecordT>
void IdAccessor<ESXRecordT>::setId(ESXRecordT& record, const QString& id) const
{
	record.id = id;
}

template<typename ESXRecordT>
QString IdAccessor<ESXRecordT>::getId(const ESXRecordT& record) const
{
	return record.id;
}

template<typename ESXRecordT, typename IdAccessorT = IdAccessor<ESXRecordT>>
class Collection : public BaseCollection
{
public:
	typedef ESXRecordT ESXRecord;

private:
	QVector<Record<ESXRecordT>> records;
	QMap<QString, int> indexes;

	// Not implemented
	Collection(const Collection&);
	Collection& operator=(const Collection&);

public:
	Collection();

	virtual int size() const;
	virtual QString getId(const int index) const;
	virtual int getIndex(const QString& id) const;
	virtual int searchId(const QString& id) const;
	virtual QVector<QString> getIdList(bool listDeleted = true) const;
	virtual void replace(const int index, const BaseRecord& record);
	virtual void insertRecord(const BaseRecord& record, int index);
	virtual void appendRecord(const BaseRecord& record);
	virtual const Record<ESXRecordT>& getRecord(const int index) const;
	virtual const Record<ESXRecordT>& getRecord(const QString& id) const;
	virtual int getAppendIndex(const QString& id) const;
};

template<typename ESXRecordT, typename IdAccessorT>
Collection<ESXRecordT, IdAccessorT>::Collection()
{
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::getIndex(const QString& id) const
{
	int index = searchId(id);

	if (index == NOT_FOUND)
	{
		throw std::runtime_error("Invalid id: " + id.toStdString());
	}
	else
	{
		return index;
	}
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::searchId(const QString& id) const
{
	QString lowerId = id.toLower();
	QMap<QString, int>::const_iterator it = indexes.find(lowerId);

	if (it == indexes.end())
	{
		return NOT_FOUND;
	}
	else
	{
		return it.value();
	}
}

template<typename ESXRecordT, typename IdAccessorT>
QVector<QString> Collection<ESXRecordT, IdAccessorT>::getIdList(bool listDeleted) const
{
	QVector<QString> ids;

	for (QMap<QString, int>::const_iterator it = indexes.begin(); it != indexes.end(); ++it)
	{
		if (listDeleted || !records.at(it.value()).isDeleted())
		{
			ids.push_back(IdAccessorT().getId(records.at(it.value()).get()));
		}
	}

	return ids;
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::replace(int index, const BaseRecord& record)
{
	records.replace(index, dynamic_cast<const Record<ESXRecordT>&>(record));
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::insertRecord(const BaseRecord& record, int index)
{
	const Record<ESXRecordT>& rec = dynamic_cast<const Record<ESXRecordT>&>(record);
	records.insert(records.begin() + index, rec);

	if (index < static_cast<int>(records.size() - 1))
	{
		for (QMap<QString, int>::iterator it = indexes.begin(); it != indexes.end(); ++it)
		{
			if (it.value() >= index)
			{
				++(it.value());
			}
		}
	}

	indexes.insert(IdAccessorT().getId(rec.get()), index);
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::appendRecord(const BaseRecord& record)
{
	insertRecord(record, getAppendIndex(IdAccessorT().getId(dynamic_cast<const Record<ESXRecordT>&>(record).get())));
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::size() const
{
	return records.size();
}

template<typename ESXRecordT, typename IdAccessorT>
QString Collection<ESXRecordT, IdAccessorT>::getId(const int index) const
{
	return IdAccessorT().getId(records[index].get());
}

template<typename ESXRecordT, typename IdAccessorT>
const Record<ESXRecordT>& Collection<ESXRecordT, IdAccessorT>::getRecord(int index) const
{
	return records.at(index);
}

template<typename ESXRecordT, typename IdAccessorT>
const Record<ESXRecordT>& Collection<ESXRecordT, IdAccessorT>::getRecord(const QString& id) const
{
	int index = getIndex(id);
	return records.at(index);
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::getAppendIndex(const QString& id) const
{
	return static_cast<int>(records.size());
}

#endif // COLLECTION_H
