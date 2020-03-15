#include "idtable.hpp"
#include "basecolumn.hpp"
#include "baseidtable.hpp"

IdTable::IdTable(BaseCollection* idCollection, unsigned int features) :
    BaseIdTable(features),
    collection(collection)
{

}

IdTable::~IdTable()
{

}

int IdTable::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return collection->size();
}

int IdTable::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return collection->getColumns();
}

QVariant IdTable::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.column() < 0)
    {
        return QVariant();
    }

    if (role == BaseColumn::Role_Display)
    {
        return QVariant(collection->getColumn(index.column()).displayType);
    }
    if (role == BaseColumn::Role_ColumnId)
    {
        return QVariant(getColumnId(index.column()));
    }
    if (role != Qt::DisplayRole && role != Qt::EditRole)
    {
        return QVariant();
    }
    if (role == Qt::EditRole && !collection->getColumn(index.column()).isEditable())
    {
        return QVariant();
    }

    return collection->getData(index.row(), index.column());
}

QVariant IdTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
    {
        return QVariant();
    }
    if (orientation == Qt::Horizontal)
    {
        throw std::logic_error("Horizontal header orientation invalid");
    }
    if (role == Qt::DisplayRole)
    {
        return collection->getColumn(section).getTitle();
    }
    if (role == BaseColumn::Role_Flags)
    {
        return collection->getColumn(section).flags;
    }
    if (role == BaseColumn::Role_Display)
    {
        return collection->getColumn(section).displayType;
    }
    if (role == BaseColumn::Role_ColumnId)
    {
        return getColumnId(section);
    }

    return QVariant();
}