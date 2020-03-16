#include "data.hpp"

#include "../doc/messages.hpp"
#include "../world/ckid.hpp"
#include "../world/idtable.hpp"
#include "../../../files/esm/esmreader.hpp"

#include <QAbstractItemModel>

Data::Data(const QStringList& files, const FilePaths& paths)
    : contentFiles(files), paths(paths)
{
    addModel(new IdTable(&gameSettings), CkId::Type_Gmst);
}

int Data::preload(const QString& filename, bool base_)
{
    reader.reset(new ESMReader(paths.dataDir.path() + "/" + filename));
    reader->open();
    base = base_;

    if (!base)
    {
        MetaData metaData_;
        metaData_.id = "esm::metadata";
        metaData_.load(*reader);

        metaData.appendRecord(Record<MetaData>(State::State_ModifiedOnly, 0, &metaData_));
    }

    return reader->recordCount();
}

bool Data::continueLoading(Messages& messages)
{
    if (!reader->isLeft())
    {
        return true;
    }
    else
    {
        NAME name = reader->readName();

        switch (name)
        {
        case 'GRUP': reader->skipGrupHeader();            break;
        case 'GMST': gameSettings.load(*reader, base);    break;
        default:
        {
            messages.append(CkId::Type_LoadingLog, "Unknown record encountered!");
            reader->skipRecord();
            break;
        }
        }

        return false;
    }
}

void Data::addModel(QAbstractItemModel* model, CkId::Type type, bool update)
{
    models.push_back(model);
    modelIndexes.insert(type, model);

    if (update)
    {
        connect(model, &QAbstractItemModel::dataChanged,
            this, &Data::dataChanged);
    }
}

QAbstractItemModel* Data::getTableModel(const CkId& id)
{
    auto it = modelIndexes.find(id.getType());

    if (it == modelIndexes.end())
    {
        throw std::logic_error("No table model available for " + id.toString().toStdString());
    }

    return it.value();
}

void Data::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    if (topLeft.column() <= 0)
    {
        emit idListChanged();
    }
}
