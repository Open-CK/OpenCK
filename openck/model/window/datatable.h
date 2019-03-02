#ifndef DATATABLE_H
#define DATATABLE_H

#include "../files/esm/esmreader.h"

#include <QAbstractTableModel>

struct FileInfo
{
    QString fileName;
    QString author;
    QString description;
    Flags flags;
    float version;
    QStringList masters;
};

class DataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataTable(const QString& path, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    FileInfo getInfoAtSelected(const QModelIndex& selected);

private:
    FileInfo getFileInfo(QString fileName, Header header);

    QVector<FileInfo> filesInfo;
};

#endif // DATATABLE_H
