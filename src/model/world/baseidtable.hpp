#ifndef BASE_ID_TABLE_H
#define BASE_ID_TABLE_H

#include "columns.hpp"

#include <QAbstractTableModel>

class BaseIdTable : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Features
    {
        Feature_Constant = 1,
        Feature_AllowTouch = 2,
        Feature_ViewId = 3
    };

public:
    BaseIdTable(unsigned int features);

    virtual QModelIndex getModelIndex(const QString& id, int column) const = 0;
    virtual int searchColumnIndex(ColumnId id) const = 0;
    virtual int findColummnIndex(ColumnId id) const = 0;

    virtual bool isDeleted(const QString& id) const = 0;
    virtual int getColumnId(int column) const = 0;
    
    unsigned int getFeatures() const;

private:
    unsigned int features;
};

#endif // BASE_ID_TABLE_H