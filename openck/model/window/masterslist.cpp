#include "masterslist.h"

MastersList::MastersList(QObject* parent)
{
}

int MastersList::rowCount(const QModelIndex& parent) const
{
    return list.size();
}

int MastersList::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant MastersList::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return list.at(index.row());
    }

    return QVariant();
}

QVariant MastersList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return "Filename";
    }
}

void MastersList::update(FileInfo info)
{
    list.clear();

    for (auto master: info.masters)
    {
        list.push_back(master);
    }

    QModelIndex topLeft(index(0, 0));
    QModelIndex bottomRight(index(rowCount(), columnCount()));
    emit dataChanged(topLeft, bottomRight);
}
