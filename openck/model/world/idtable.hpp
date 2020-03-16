#ifndef ID_TABLE_H
#define ID_TABLE_H

#include "basecollection.hpp"
#include "baseidtable.hpp"
#include "columns.hpp"

#include <QVariant>

class BaseRecord;

class IdTable : public BaseIdTable
{
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

    virtual QModelIndex getModelIndex(const QString& id, int column) const;
    virtual int searchColumnIndex(ColumnId id) const;
    virtual int findColummnIndex(ColumnId id) const;
    void reorderRows(int baseIndex, const QVector<int>& newOrder);
    virtual int getColumnId(int column) const;

    void addRecord(const QString& id, CkId::Type type = CkId::Type_None);
    void addRecordWithData(const QString& id, const QMap<int, QVariant>& data, CkId::Type type = CkId::Type_None);
    void cloneRecord(const QString& src, const QString& dest, CkId::Type type = CkId::Type_None);
    bool touchRecord(const QString& id);
    QString getId(int row) const;
    void setRecord(const QString& id, const BaseRecord& record, CkId::Type type = CkId::Type_None);
    const BaseRecord& getRecord(const QString& id) const;

    virtual bool isDeleted(const QString& id) const;
    virtual QPair<CkId, QString> view(int row) const;

protected:
    virtual BaseCollection* idCollection() const;

private:
    BaseCollection* collection;

    IdTable(const IdTable&);
    IdTable& operator= (const IdTable&);
};

#endif // ID_TABLE_H