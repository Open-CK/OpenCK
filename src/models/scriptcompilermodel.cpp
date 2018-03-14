#include <models/scriptcompilermodel.h>

namespace models
{
    ScriptCompilerModel::ScriptCompilerModel(QObject* parent)
        : QAbstractItemModel(parent)
    {
    }

    QModelIndex ScriptCompilerModel::index(int row, int column, const QModelIndex& parent) const
    {
        return QModelIndex();
    }

    QModelIndex ScriptCompilerModel::parent(const QModelIndex& child) const
    {
        return QModelIndex();
    }

    int ScriptCompilerModel::rowCount(const QModelIndex& parent) const
    {
        return int();
    }

    int ScriptCompilerModel::columnCount(const QModelIndex& parent) const
    {
        return int();
    }

    QVariant ScriptCompilerModel::data(const QModelIndex& index, int role) const
    {
        return QVariant();
    }
}