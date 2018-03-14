#ifndef SCRIPTMANAGERMODEL_H
#define SCRIPTMANAGERMODEL_H

#include <QAbstractItemModel>

namespace models
{
    enum class ScriptStatus
    {
        NONE,
        DIRTY,
        COMPILE_SUCCESS,
        COMPILE_FAIL
    };

    struct ScriptData
    {
        QString name;
        QString tmpPath;
        ScriptStatus status{ ScriptStatus::NONE };
    };

    class ScriptManagerModel : public QAbstractItemModel
    {
    public:
        ScriptManagerModel(QObject* parent = Q_NULLPTR);
        ScriptManagerModel(const ScriptManagerModel&) = default;
        ScriptManagerModel& operator=(const ScriptManagerModel&) = default;
        ~ScriptManagerModel() = default;

        virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex & child) const override;
        virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
        virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
        virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

        void AddNewScript(const QString& name);

    private:
        QVector<ScriptData> scriptData;
    };
}

#endif