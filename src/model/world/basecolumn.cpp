#include "basecolumn.hpp"
#include "columns.hpp"

BaseColumn::BaseColumn(int columnId, Display displayType, int flags) :
    columnId(columnId),
    displayType(displayType),
    flags(flags)
{

}

BaseColumn::~BaseColumn() 
{

}

bool BaseColumn::isUserEditable() const
{
    return isEditable();
}

QString BaseColumn::getTitle() const
{
    return getColumnName(static_cast<ColumnId>(columnId));
}

int BaseColumn::getId() const
{
    return columnId;
}

bool BaseColumn::isId(Display display)
{
    static const Display ids[] =
    {
        Display_Id,

        Display_None
    };

    for (int i = 0; ids[i] != Display_None; i++)
    {
        if (ids[i] == display)
        {
            return true;
        }
    }

    return false;
}

bool BaseColumn::isText(Display display)
{
    return display == Display_String || display == Display_LongString;
}

void NestableColumn::addColumn(NestableColumn* column)
{
    nestedColumns.push_back(column);
}

const BaseColumn& NestableColumn::nestedColumn(int subColumn) const
{
    if (nestedColumns.empty())
    {
        throw std::logic_error("Tried to access nested column of a non-nest column");
    }

    return *(nestedColumns.at(subColumn));
}

NestableColumn::NestableColumn(int columnId, BaseColumn::Display displayType, int flag) :
    BaseColumn(columnId, displayType, flag)
{

}

NestableColumn::~NestableColumn()
{
    for (int i = 0; i < nestedColumns.size(); i++)
    {
        delete nestedColumns[i];
    }
}

bool NestableColumn::hasChildren() const
{
    return !nestedColumns.isEmpty();
}

NestedChildColumn::NestedChildColumn(int id, BaseColumn::Display display, int flags, bool isEditable) :
    NestableColumn(id, display, flags),
    isEditable(isEditable)
{

}

bool NestedChildColumn::editable() const
{
    return isEditable;
}
