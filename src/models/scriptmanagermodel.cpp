#include <models/scriptmanagermodel.h>
#include <QDebug>

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
        return 4;
    }

    QVariant ScriptManagerModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
            return {};

        if (index.row() >= scriptData.size())
            return {};

        auto& scData = scriptData[index.row()];
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0: return scData.name;
            case 1: return statusCodeToString(static_cast<int>(scData.status));
            default: return {};
            }
        }
        else if (role == Qt::UserRole) {
            switch (index.column()) {
            case 0: return scData.name;
            case 1: return scData.tmpPath;
            case 2: return static_cast<int>(scData.status);
            case 3: return scData.priority;
            default: return {};
            }
        }

        return {};
    }
    
    bool ScriptManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid()) {

            auto& scData = scriptData[index.row()];
            if (role == Qt::DisplayRole) {
                switch (index.column()) {
                case 0: scData.name = value.toString(); break;
                case 1: scData.status = static_cast<ScriptStatus>(value.toInt()); break;
                default: return false;
                }
            }
            else if (role == Qt::UserRole) {
                switch (index.column()) {
                case 0: scData.name = value.toString(); break;
                case 1: scData.tmpPath = value.toString(); break;
                case 2: scData.status = static_cast<ScriptStatus>(value.toInt()); break;
                case 3: scData.priority = value.toInt(); break;
                default: return false;
                }
            }

            emit dataChanged(index, index);
            return true;
        }

        return false;
    }

    QVariant ScriptManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case 0: return "Name";
            case 1: return "Status";
            }
        }
        return {};
    }

    bool ScriptManagerModel::insertRows(int row, int count, const QModelIndex& parent)
    {
        beginInsertRows({}, row, row + (count - 1));
        scriptData.insert(row, count, {});
        endInsertRows();

        return true;
    }

    bool ScriptManagerModel::removeRows(int row, int count, const QModelIndex& parent)
    {
        beginRemoveRows({}, row, row + (count - 1));
        scriptData.remove(row, count);
        endRemoveRows();

        return true;
    }

    QString ScriptManagerModel::statusCodeToString(int code) const
    {
        ScriptStatus status = static_cast<ScriptStatus>(code);
        switch (status) {
        case ScriptStatus::NONE: return "";
        case ScriptStatus::DIRTY: return "Dirty";
        case ScriptStatus::COMPILE_WAIT: return "Compilation Queued";
        case ScriptStatus::COMPILE_SUCCESS: return "Compile Success";
        case ScriptStatus::COMPILE_FAIL: return "Compile Fail";
        default: return "";
        }
    }
}
