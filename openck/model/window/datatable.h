#ifndef DATATABLE_H
#define DATATABLE_H

#include <QAbstractTableModel>

class DataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataTable(const QString& path, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    std::vector<QString> fileNames;
};

#endif // DATATABLE_H
