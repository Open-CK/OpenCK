#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include <Qt>
#include <QString>

struct BaseColumn
{
	enum EditMode
	{
		Edit_None,
		Edit_Full,
		Edit_FixedRows
	};

	enum Role
	{
		Role_Flags = Qt::UserRole,
		Role_Display = Qt::UserRole + 1,
		Role_ColumnId = Qt::UserRole + 2
	};

	enum Flags
	{
		Flag_Table = 1
	};

	enum Display
	{
		Display_None,
		Display_String,
		Display_LongString,

		Display_GameSetting,

		Display_SignedInteger8,
		Display_SignedInteger16,
		Display_UnsignedInteger8,
		Display_UnsignedInteger16,
		Display_SignedInteger32,
		Display_UnsignedInteger32,
		Diaplay_Float,
		Display_Double,
		Display_Boolean,
		Display_Var,
		Display_Id,
	};

	int columnId;
	int flags;
	Display displayType;

	BaseColumn(int columnId, Display displayType, int flag);

	virtual ~BaseColumn();

	virtual bool isEditable() const = 0;
	virtual bool isUserEditable() const;
	virtual QString getTitle() const;
	virtual int getId() const;
	
	static bool isId(Display display);
	static bool isText(Display display);
};

#endif // BASE_COLUMN_H