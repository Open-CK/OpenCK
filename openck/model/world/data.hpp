#ifndef WORLDDATA_H
#define WORLDDATA_H

#include "idcollection.hpp"
#include "metadata.hpp"
#include "../../../files/filepaths.hpp"
#include "../../../files/esm/esmreader.hpp"
#include "../../../files/esm/gmst.hpp"
#include "../../../files/esm/tes4.hpp"

#include <QObject>
#include <QStringList>

class Messages;
class QAbstractItemModel;

class Data : public QObject
{
    Q_OBJECT

public:
    Data(const QStringList& files, const FilePaths& paths);

    int preload(const QString& filename, bool base);
    bool continueLoading(Messages& messages);

    void addModel(QAbstractItemModel* model, CkId::Type type, bool update = true);
    QAbstractItemModel* getTableModel(const CkId& id);

signals:
    void idListChanged();

private:
    std::unique_ptr<ESMReader> reader;

    QStringList contentFiles;
    FilePaths paths;
    bool base;
    
    IdCollection<GameSetting> gameSettings;
    Collection<MetaData> metaData;

    QVector<QAbstractItemModel*> models;
    QMap<CkId::Type, QAbstractItemModel*> modelIndexes;

private slots:
    void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
};

#endif // WORLDDATA_H
