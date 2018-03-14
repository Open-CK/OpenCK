#include <models/scriptmanagermodel.h>

namespace models
{
    ScriptManagerModel::ScriptManagerModel(QObject* parent)
        : QAbstractItemModel(parent)
    {
    }

    QModelIndex ScriptManagerModel::index(int row, int column, const QModelIndex& parent) const
    {
        return createIndex(row, column, nullptr);
    }

    QModelIndex ScriptManagerModel::parent(const QModelIndex& child) const
    {
        return {};
    }

    int ScriptManagerModel::rowCount(const QModelIndex& parent) const
    {
        return scriptData.count();
    }

    int ScriptManagerModel::columnCount(const QModelIndex& parent) const
    {
        return 1;
    }

    QVariant ScriptManagerModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
            return {};

        if (index.row() >= scriptData.size())
            return {};

        if (role == Qt::DisplayRole && index.column() == 0) {
            return scriptData[index.row()].name;
        }
        return {};
    }
    
    bool ScriptManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && role == Qt::DisplayRole) {
            scriptData[index.row()].name = value.toString();

            emit dataChanged(index, index);

            return true;
        }
        return false;
    }

    QVariant ScriptManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        return {};
    }

    bool ScriptManagerModel::insertRows(int row, int count, const QModelIndex& parent)
    {
        beginInsertRows({}, row, row + (count - 1));
        scriptData.insert(row, count, {});
        endInsertRows();

        /*QModelIndex top = createIndex(scriptData.count() - 1, 0, nullptr);
        QModelIndex bottom = createIndex(scriptData.count() - 1, 0, nullptr);
        emit dataChanged(top, bottom);*/

        return true;
    }

    bool ScriptManagerModel::removeRows(int row, int count, const QModelIndex& parent)
    {
        if ((row + count) >= scriptData.size())
            return false;

        beginRemoveRows({}, row, row + (count - 1));
        scriptData.remove(row, count);
        endRemoveRows();

        return true;
    }
}
