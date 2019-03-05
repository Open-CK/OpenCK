#ifndef DATATABLE_H
#define DATATABLE_H

#include "fileinfo.h"

#include <QAbstractTableModel>

const int NONE_ACTIVE = -1;

class DataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataTable(const QString& path, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    FileInfo getInfoAtSelected(const QModelIndex& selected);
    void setActive(const QModelIndex& index);
    bool isPlugin(const QModelIndex& index) const;

public slots:
    void doubleClicked(const QModelIndex& index);

private:
    FileInfo getFileInfo(QString fileName, Header header);
    QVector<FileInfo> filesInfo;
    QVector<bool> selected;
    int active;

signals:
    void newFileSelected(FileInfo info);
};

#endif // DATATABLE_H
