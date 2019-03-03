#include "datatable.h"

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
            "Failed to find data files.\n"
            "Please ensure DataDirectory setting in config.ini is correct."
        );
    }

    // TODO: Sort between plugins/masters
    files.sort();

    for (auto file: files)
    {
        try
        {
            QString fileName{ path + "/" + file };
            ESMReader reader{ fileName };
            reader.open();
            FileInfo info = getFileInfo(file, reader.getHeader());
            filesInfo.push_back(info);
        }
        catch (std::runtime_error& e)
        {
            msgBoxCritical(e.what());
        }
    }
}

int DataTable::rowCount(const QModelIndex &parent) const
{
    return filesInfo.size();
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
            return filesInfo.at(index.row()).fileName;
        case 1:
        {
            if (filesInfo.at(index.row()).flags.test(FileFlag::Master))
            {
                return "Master File";
            }
            else
            {
                return "Plugin File";
            }
        }
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
            return QString("TES File");
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

FileInfo DataTable::getInfoAtSelected(const QModelIndex &selected)
{
    FileInfo info{ filesInfo.at(selected.row()) };
    emit newFileSelected(info);
    return info;
}

FileInfo DataTable::getFileInfo(QString fileName, Header header)
{
    FileInfo info;
    info.fileName = fileName;
    info.author = header.author;
    info.description = header.description;
    info.flags.val = header.flags.val;
    info.version = header.version;

    for (auto master: header.masters)
    {
        info.masters << master.name;
    }

    return info;
}
