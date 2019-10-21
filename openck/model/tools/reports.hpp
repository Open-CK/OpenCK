#ifndef REPORTS_H
#define REPORTS_H

#include "../doc/messages.hpp"
#include "../world/ckid.hpp"

#include <QAbstractTableModel>
#include <QString>
#include <QVector>

class ReportModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	ReportModel(bool fieldColumn = false, bool levelColumn = true);
	
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	
	virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
	void add(const Message& message);
	QString getHint(int row) const;
	const CkId getCkId(int row) const;

	int countErrors() const;
	void clear();

private:
	QVector<Message> rows;

	enum Columns
	{
		Column_Type = 0, 
		Column_Id = 1, 
		Column_Hint = 2,
		Columns = 3,
	};

	int columnDescription;
	int columnField;
	int columnLevel;
};

#endif // REPORTS_H