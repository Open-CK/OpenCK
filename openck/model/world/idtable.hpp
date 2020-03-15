#ifndef ID_TABLE_H
#define ID_TABLE_H

#include "basecollection.hpp"
#include "baseidtable.hpp"
#include "columns.hpp"

#include <QVariant>

class IdTable : public BaseIdTable
{
	struct BaseRecord;

	Q_OBJECT

public:
	IdTable(BaseCollection* idCollection, unsigned int features = 0);
	virtual ~IdTable();

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& parent, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	virtual Qt::ItemFlags flags(const QModelIndex& index) const;
	virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex& index) const;

protected:
	virtual BaseCollection* idCollection() const;

private:
	BaseCollection* collection;

	IdTable(const IdTable&);
	IdTable& operator= (const IdTable&);
};

#endif // ID_TABLE_H