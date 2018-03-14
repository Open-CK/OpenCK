#ifndef SCRIPTCOMPILERMODEL_H
#define SCRIPTCOMPILERMODEL_H

#include <QAbstractItemModel>
#include <QVector>

namespace models
{
    class ScriptCompilerModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        ScriptCompilerModel(QObject* parent = Q_NULLPTR);
        ScriptCompilerModel(const ScriptCompilerModel&) = default;
        ScriptCompilerModel& operator=(const ScriptCompilerModel&) = default;
        ~ScriptCompilerModel() = default;

        virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex & child) const override;
        virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    };
}

#endif