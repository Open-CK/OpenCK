#include "datatable.h"

#include <QBrush>
#include <QDir>

DataTable::DataTable(const QString& path, QObject* parent)
    : QAbstractTableModel(parent)
{
    QDir dataDir{ path };
    QStringList filters;
    filters << "*.esm" << "*.esp" << "*.esl";
    dataDir.setNameFilters(filters);
    QStringList files{ dataDir.entryList() };

    // TODO: Sort between plugins/masters
    files.sort();

    for (auto file: files)
    {
        fileNames.push_back(file);
    }
}

int DataTable::rowCount(const QModelIndex &parent) const
{
    return fileNames.size();
}

int DataTable::columnCount(const QModelIndex &parent) const
{
    // TODO: plugin/master flag and column
    return 1;
}

QVariant DataTable::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return fileNames.at(index.row());
    }

    return QVariant();
}

QVariant DataTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return QString("Filename");
        }
    }
    else
    {
        switch (role)
        {
            case Qt::TextAlignmentRole:
                return Qt::AlignLeft;
        }
    }

    return QVariant();
}
