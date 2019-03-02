#include "datatable.h"

#include "../files/esm/esmreader.h"
#include "../openck/view/messageboxhelper.h"

#include <QBrush>
#include <QDir>
#include <QMessageBox>

DataTable::DataTable(const QString& path, QObject* parent)
    : QAbstractTableModel(parent)
{
    QDir dataDir{ path };

    QStringList filters;
    filters << "*.esm" << "*.esp" << "*.esl";
    dataDir.setNameFilters(filters);
    QStringList files{ dataDir.entryList() };

    if (!dataDir.exists() || files.empty())
    {
        msgBoxCritical(
            "failed to find data files.\n"
            "Please ensure DataDirectory setting in config.ini is correct."
        );
    }

    // TODO: Sort between plugins/masters
    files.sort();

    for (auto file: files)
    {
        try
        {
            ESMReader reader(QString(path + "/" + file), file);
            reader.open();
            fileNames.push_back(file);
        }
        catch (std::runtime_error& e)
        {
            msgBoxCritical(e.what());
        }
    }
}

int DataTable::rowCount(const QModelIndex &parent) const
{
    return fileNames.size();
}

int DataTable::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant DataTable::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case 0:
                return fileNames.at(index.row());
        }
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
            case 1:
                return QString("Status");
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
