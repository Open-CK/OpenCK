#ifndef SCRIPTCOMPILERMODEL_H
#define SCRIPTCOMPILERMODEL_H

#include <QSortFilterProxyModel>
#include <QVector>

namespace models
{
    class ScriptCompilerModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        ScriptCompilerModel(QObject* parent = Q_NULLPTR);
        ScriptCompilerModel(const ScriptCompilerModel&) = default;
        ScriptCompilerModel& operator=(const ScriptCompilerModel&) = default;
        ~ScriptCompilerModel() = default;

        virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
        virtual bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

        virtual void setSourceModel(QAbstractItemModel* model) override;

    private slots:
        void on_ScriptCompilerModel_dataChanged(const QModelIndex& tl, const QModelIndex& br);
    };
}

#endif