#include "columns.hpp"
#include "basecolumn.hpp"

struct ColumnDesc
{
    int id;
    QString name;
};

const ColumnDesc columnNames[] =
{
    { ColumnId_Id, "ID" },
    { ColumnId_Value, "Value" },

    { ColumnId_End, 0 }
};

QString getColumnName(ColumnId column)
{
    for (int i = 0; i < ColumnId_End; i++)
    {
        if (column == columnNames[i].id)
        {
            return columnNames[i].name;
        }
    }

    return "";
}

int getColumnId(const QString& name)
{
    QString lower = name.toLower();

    for (int i = 0; i < ColumnId_End; i++)
    {
        if (lower == name.toLower())
        {
            return columnNames[i].id;
        }
    }

    return -1;
}