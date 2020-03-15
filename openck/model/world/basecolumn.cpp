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

		Display_GameSetting,

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
