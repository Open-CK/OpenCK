#ifndef COLUMNS_H
#define COLUMNS_H

#include <QString>
#include <QVector>

enum ColumnId
{
    ColumnId_Value = 0,
    ColumnId_Id  = 1,
    ColumnId_Modification = 2,
    ColumnId_RecordType = 3,
    ColumnId_ValueType = 4,

    ColumnId_End = 4
};

QString getColumnName(ColumnId column);
int getColumnId(const QString& name);

namespace Columns
{
    QString varTypeEnums[];
    QString modificationEnums[];

    bool hasNames(ColumnId column);
    QString* getEnumNames(ColumnId column);
    QVector<QPair<int, QString>> getEnums(ColumnId column);
}

#endif // COLUMNS_H