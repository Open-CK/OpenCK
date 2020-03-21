#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include "record.hpp"

#include <Qt>
#include <QString>
#include <QVariant>
#include <QVector>
#include <stdexcept>

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
        Flag_Table = 1,
        Flag_Dialogue = 2,
        Flag_Dialogue_List = 4,
        Flag_Dialogue_Refresh = 8
    };

    enum Display
    {
        Display_None,
        Display_String,
        Display_LongString,

        Display_RecordState,

        Display_GmstVarType,

        Display_NestedHeader,

        Display_SignedInteger8,
        Display_SignedInteger16,
        Display_UnsignedInteger8,
        Display_UnsignedInteger16,
        Display_SignedInteger32,
        Display_UnsignedInteger32,
        Display_Float,
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

class NestableColumn : public BaseColumn
{
public:
    NestableColumn(int columnId, Display displayType, int flag);
    ~NestableColumn();

    void addColumn(NestableColumn* column);
    const BaseColumn& nestedColumn(int subColumn) const;

    bool hasChildren() const;

private:
    QVector<NestableColumn*> nestedColumns;
};

template<typename ESXRecord>
struct Column : public NestableColumn
{
    Column(int columnId, Display displayType, int flags = Flag_Table | Flag_Dialogue) : 
        NestableColumn(columnId, displayType, flags) 
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const = 0;

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {
        throw std::logic_error("Column " + getTitle().toStdString() + " is not editable");
    }
};

template <typename ESXRecord>
struct NestedParentColumn : public Column<ESXRecord>
{
    NestedParentColumn(int id, int flags, bool fixedRows = false) :
        Column<ESXRecord>(id, BaseColumn::Display_NestedHeader, flags),
        fixedRows(fixedRows)
    {

    }

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        if (fixedRows)
        {
            return QVariant::fromValue(BaseColumn::Edit_FixedRows);
        }
        else
        {
            return QVariant::fromValue(BaseColumn::Edit_Full);
        }
    }

    virtual bool isEditable() const
    {
        return true;
    }

private:
    bool fixedRows;
};

struct NestedChildColumn : public NestableColumn
{
    NestedChildColumn(int id, Display display, int flags = BaseColumn::Flag_Dialogue, bool isEditable = true);

    virtual bool editable() const;

private:
    bool isEditable;
};

#endif // BASE_COLUMN_H