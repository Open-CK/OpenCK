#include "reports.hpp"

#include <sstream>

ReportModel::ReportModel(bool fieldColumn, bool levelColumn) :
	columnField(-1), columnLevel(-1)
{
	int index = Columns;

	if (levelColumn)
	{
		columnLevel = index;
		index++;
	}
	if (fieldColumn)
	{
		columnField = index;
		index++;
	}

	columnDescription = index;
}

int ReportModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
		return 0;
	}
	else
	{
		return rows.size();
	}
}

int ReportModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
		return 0;
	}
	else
	{
		return columnDescription + 1;
	}
}

QVariant ReportModel::data(const QModelIndex& index, int role) const
{
	if (role != Qt::DisplayRole && role != Qt::UserRole)
	{
		return QVariant();
	}

	switch (index.column())
	{
	case Column_Hint:
	{
		return rows.at(index.row()).hint;
	}
	}

	if (index.column() == columnDescription)
	{
		return rows.at(index.row()).message;
	}

	if (index.column() == columnLevel)
	{
		return Message::toString(rows.at(index.row()).level);
	}

	return QVariant();
}

QVariant ReportModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole || orientation == Qt::Vertical)
	{
		return QVariant();
	}

	switch (section)
	{
	case Column_Type:
	{
		return "Type";
	}
	case Column_Id:
	{
		return "ID";
	}
	}

	if (section == columnDescription)
	{
		return "Description";
	}
	else if (section == columnField)
	{
		return "Field";
	}
	else if (section == columnLevel)
	{
		return "Level";
	}

	return "-";
}

bool ReportModel::removeRows(int row, int count, const QModelIndex& parent)
{
	if (parent.isValid())
	{
		return false;
	}

	if (count > 0)
	{
		beginRemoveRows(parent, row, row + count - 1);
		rows.erase(rows.begin()+row, rows.begin()+row+count);
		endRemoveRows();
	}

	return true;
}

void ReportModel::add(const Message& message)
{
	beginInsertRows(QModelIndex(), rows.size(), rows.size());
	rows.push_back(message);
	endInsertRows();
}

QString ReportModel::getHint(int row) const
{
	return rows.at(row).hint;
}

void ReportModel::clear()
{
	if (!rows.empty())
	{
		beginRemoveRows(QModelIndex(), 0, rows.size() - 1);
		rows.clear();
		endRemoveRows();
	}
}

int ReportModel::countErrors() const
{
	int count = 0;

	for (QVector<Message>::const_iterator it = rows.begin(); it != rows.end(); ++it)
	{
		if (it->level == Message::Error || it->level == Message::Critical)
		{
			count++;
		}
	}

	return count;
}