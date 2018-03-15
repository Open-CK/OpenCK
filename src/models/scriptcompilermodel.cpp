#include <models/scriptcompilermodel.h>
#include <data/scriptmanagerdata.h>

namespace models
{
    ScriptCompilerModel::ScriptCompilerModel(QObject* parent)
        : QSortFilterProxyModel(parent)
    {
    }

    bool ScriptCompilerModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
    {
        QVariant leftData = sourceModel()->data(left, Qt::UserRole);
        QVariant rightData = sourceModel()->data(right, Qt::UserRole);
        return leftData.toInt() < rightData.toInt();
    }

    bool ScriptCompilerModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
    {
        QModelIndex scriptStatusIndex = sourceModel()->index(sourceRow, 2);
        QModelIndex priorityIndex = sourceModel()->index(sourceRow, 3);
        return sourceModel()->data(scriptStatusIndex, Qt::UserRole).toInt() == static_cast<int>(ScriptStatus::COMPILE_WAIT) &&
               sourceModel()->data(priorityIndex, Qt::UserRole).toInt() >= 0;
    }

    void ScriptCompilerModel::setSourceModel(QAbstractItemModel* model)
    {
        QSortFilterProxyModel::setSourceModel(model);
        connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(on_ScriptCompilerModel_dataChanged(const QModelIndex&, const QModelIndex&)));
    }

    void ScriptCompilerModel::on_ScriptCompilerModel_dataChanged(const QModelIndex& tl, const QModelIndex& br)
    {
        Q_UNUSED(tl);
        Q_UNUSED(br);
        invalidateFilter();
    }
}