#ifndef COLUMNS_H
#define COLUMNS_H

#include <QString>

enum ColumnId
{
    ColumnId_Value = 0,
    ColumnId_Id  = 1,
    ColumnId_Modification = 2,
    ColumnId_RecordType = 3,

    ColumnId_End = 4
};

QString getColumnName(ColumnId column);

int getColumnId(const QString& name);

#endif // COLUMNS_H