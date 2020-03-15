#ifndef COLLECTION_H
#define COLLECTION_H

#include "basecollection.hpp"
#include "basecolumn.hpp"
#include "record.hpp"

#include <algorithm>

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
	QVector<Column<ESXRecordT>*> columns;

	// Not implemented
	Collection(const Collection&);
	Collection& operator=(const Collection&);

protected:
	const QMap<QString, int>& getIdMap() const;
	const QVector<Record<ESXRecordT>>& getRecords() const;

	bool reorderRowsImp(int baseIndex, const QVector<int>& newOrder);
	int cloneRecordImp(const QString& src, const QString& dest, CkId::Type type);
	int touchRecordImp(const QString& id);

public:
	Collection();
	virtual ~Collection();

	void add(const ESXRecordT& record);

	virtual int size() const;
	virtual QString getId(const int index) const;
	virtual int getIndex(const QString& id) const;
	virtual int getColumns() const;
	virtual QVariant getData(int index, int column) const;
	virtual void setData(int index, int column, const QVariant& data);
	virtual const BaseColumn& getColumn(int column) const;
	virtual void merge();
	virtual void purge();
	virtual void removeRows(int index, int count);
	virtual void appendBlankRecord(const QString& id, CkId::Type = CkId::Type_None);
	virtual void cloneRecord(const QString& src, const QString& dest, const CkId::Type type);
	virtual bool touchRecord(const QString& id);
	virtual int searchId(const QString& id) const;
	virtual QVector<QString> getIds(bool listDeleted = true) const;
	virtual void replace(const int index, const BaseRecord& record);
	virtual void insertRecord(const BaseRecord& record, int index, CkId::Type = CkId::Type_None);
	virtual void appendRecord(const BaseRecord& record, CkId::Type = CkId::Type_None);
	virtual const Record<ESXRecordT>& getRecord(const int index) const;
	virtual const Record<ESXRecordT>& getRecord(const QString& id) const;
	virtual int getAppendIndex(const QString& id, CkId::Type = CkId::Type_None) const;
	virtual bool reorderRows(int baseIndex, const QVector<int>& newOrder);
	
	void addColumn(Column<ESXRecordT>* column);
	void setRecord(int index, const Record<ESXRecordT>& record);

	NestableColumn* getNestableColumn(int column) const;
};

template<typename ESXRecordT, typename IdAccessorT>
Collection<ESXRecordT, IdAccessorT>::Collection()
{
}

template<typename ESXRecordT, typename IdAccessorT>
const QMap<QString, int>& Collection<ESXRecordT, IdAccessorT>::getIdMap() const
{
	return indexes;
}

template<typename ESXRecordT, typename IdAccessorT>
const QVector<Record<ESXRecordT>>& Collection<ESXRecordT, IdAccessorT>::getRecords() const
{
	return records;
}

template<typename ESXRecordT, typename IdAccessorT>
bool Collection<ESXRecordT, IdAccessorT>::reorderRowsImp(int baseIndex, const QVector<int>& newOrder)
{
	if (!newOrder.isEmpty())
	{
		int size = newOrder.size();

		QVector<int> test(newOrder);
		std::sort(test.begin(), test.end());

		if (test.begin() != 0 || *(test.end() - 1) != size - 1)
		{
			return false;
		}

		QVector<Record<ESXRecordT>> temp(size);

		for (int i = 0; i < size; i++)
		{
			temp[newOrder[i]] = records[baseIndex + i];
			temp[newOrder[i]].setModified(temp[newOrder[i]].get());
		}

		std::copy(temp.begin(), temp.end(), records.begin() + baseIndex);

		for (auto it = indexes.begin(); it != indexes.end(); ++it)
		{
			if (it.value() >= baseIndex && it.value() < baseIndex + size)
			{
				it.value() = newOrder.at(it.value() - baseIndex) + baseIndex;
			}
		}
	}

	return true;
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::cloneRecordImp(const QString& src, const QString& dest, CkId::Type type)
{
	Record<ESXRecordT> copy;
	copy.setModified(getRecord(src).get());
	copy.state = State::State_ModifiedOnly;

	IdAccessorT().setId(copy.get(), dest);

	int index = getAppendIndex(dest, type);
	insertRecord(copy, index);

	return index;
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::touchRecordImp(const QString& id)
{
	int index = getIndex(id);
	Record<ESXRecordT>& record = records[index];

	if (record.isDeleted())
	{
		throw std::runtime_error("Attempted to touch a deleted record");
	}

	if (!record.isModified())
	{
		record.setModified(record.get());
		return index;
	}

	return -1;
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::cloneRecord(const QString& src, const QString& dest, const CkId::Type type)
{
	cloneRecordImp(src, dest, type);
}

template<typename ESXRecordT, typename IdAccessorT>
bool Collection<ESXRecordT, IdAccessorT>::touchRecord(const QString& id)
{
	return touchRecordImp(id) != -1;
}

template<typename ESXRecordT, typename IdAccessorT>
Collection<ESXRecordT, IdAccessorT>::Collection()
{

}

template<typename ESXRecordT, typename IdAccessorT>
Collection<ESXRecordT, IdAccessorT>::~Collection()
{
	for (auto it = columns.begin(); it != columns.end(); ++it)
	{
		delete* it;
	}
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::add(const ESXRecordT& record)
{
	QString id = IdAccessorT().getId(record).toLower();

	auto it = indexes.find(id);

	if (it == indexes.end())
	{
		Record<ESXRecordT> newRecord;
		newRecord.state = State::State_ModifiedOnly;
		newRecord.modifiedRecord = record;

		insertRecord(newRecord, getAppendIndex(id));
	}
	else
	{
		records[it.value()].setModified(record);
	}
}

template<typename ESXRecordT, typename IdAccessorT>
int Collection<ESXRecordT, IdAccessorT>::getColumns() const
{
	return columns.size();
}

template<typename ESXRecordT, typename IdAccessorT>
QVariant Collection<ESXRecordT, IdAccessorT>::getData(int index, int column) const
{
	return columns.at(column)->get(records.at(index));
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::setData(int index, int column, const QVariant& data)
{
	columns.at(column)->set(records[index], data);
}

template<typename ESXRecordT, typename IdAccessorT>
const BaseColumn& Collection<ESXRecordT, IdAccessorT>::getColumn(int column) const
{
	return *columns.at(column);
}

template<typename ESXRecordT, typename IdAccessorT>
NestableColumn* Collection<ESXRecordT, IdAccessorT>::getNestableColumn(int column) const
{
	if (column < 0 || column >= columns.size())
	{
		throw std::runtime_error("Column index out of range");
	}

	return columns[column];
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::addColumn(Column<ESXRecordT>* column)
{
	columns.push_back(column);
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::merge()
{
	for (auto it = records.begin(); it != records.end(); ++it)
	{
		it->merge();
	}

	purge();
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::purge()
{
	int i = 0;
	
	while (i < records.size())
	{
		if (records[i].isErased)
		{
			removeRows(i, 1);
		}
		else
		{
			i++;
		}
	}
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::removeRows(int index, int count)
{
	records.erase(records.begin() + index, records.begin() + index + count);
	auto it = indexes.begin();

	while (it != indexes.end())
	{
		if (it.value() >= index)
		{
			if (it.value() >= index + count)
			{
				it.value() -= count;
				it++;
			}
			else
			{
				indexes.erase(it++);
			}
		}
		else
		{
			++it;
		}
	}
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::appendBlankRecord(const QString& id, CkId::Type type)
{
	ESXRecordT record;
	IdAccessorT().setId(record, id);

	Record<ESXRecordT> newRecord;
	newRecord.state = State::State_ModifiedOnly;
	newRecord.modifiedRecord = record;

	insertRecord(newRecord, getAppendIndex(id, type), type);
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
QVector<QString> Collection<ESXRecordT, IdAccessorT>::getIds(bool listDeleted) const
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
void Collection<ESXRecordT, IdAccessorT>::insertRecord(const BaseRecord& record, int index, CkId::Type type)
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
void Collection<ESXRecordT, IdAccessorT>::appendRecord(const BaseRecord& record, CkId::Type type)
{
	insertRecord(record, getAppendIndex(IdAccessorT().getId(dynamic_cast<const Record<ESXRecordT>&>(record).get())), type);
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
int Collection<ESXRecordT, IdAccessorT>::getAppendIndex(const QString& id, CkId::Type type) const
{
	return static_cast<int>(records.size());
}

template<typename ESXRecordT, typename IdAccessorT>
void Collection<ESXRecordT, IdAccessorT>::setRecord(int index, const Record<ESXRecordT>& record)
{
	if (IdAccessorT().getId(records[index].get()).toLower() != IdAccessorT().getId(records[index].get()).toLower)
	{
		throw std::runtime_error("Attempted to change the ID of a record");
	}

	records[index] = record;
}

template<typename ESXRecordT, typename IdAccessorT>
bool Collection<ESXRecordT, IdAccessorT>::reorderRows(int baseIndex, const QVector<int>& newOrder)
{
	return false;
}

#endif // COLLECTION_H
