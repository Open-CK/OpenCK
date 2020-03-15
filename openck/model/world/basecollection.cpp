#include "basecollection.hpp"

#include <stdexcept>

BaseCollection::BaseCollection()
{

}

BaseCollection::~BaseCollection()
{

}

int BaseCollection::searchColumnIndex(ColumnId id) const
{
	int columns = getColumns();

	for (int i = 0; i < columns; i++)
	{
		if (getColumn(i).columnId == id)
		{
			return i;
		}
	}

	return -1;
}

int BaseCollection::findColumnIndex(ColumnId id) const
{
	int index = searchColumnIndex(id);

	if (index == -1)
	{
		throw std::logic_error("Invalid column index");
	}

	return index;
}
