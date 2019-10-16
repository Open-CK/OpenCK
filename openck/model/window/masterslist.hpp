#ifndef MASTERSTABLE_H
#define MASTERSTABLE_H

#include "fileinfo.hpp"

#include <QAbstractTableModel>

class MastersList : public QAbstractTableModel
{
    Q_OBJECT

public:
    MastersList(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    void update(FileInfo info);

private:
    QVector<QString> list;
};

#endif // MASTERSTABLE_H
