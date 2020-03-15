#ifndef BASE_COLUMN_H
#define BASE_COLUMN_H

#include <Qt>
#include <QString>
#include <QVector>

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

template<typename ESXRecordT>
struct Column : public NestableColumn
{
    Column(int columnId, Display displayType, int flags = Flag_Table | Flag_Dialogue) :
        NestableColumn(columnId, displayType, flags)
    {

    }

    virtual QVariant get(const Record<ESXRecordT>& record) const = 0;

    virtual void set(Record<ESXRecordT>& record, const QVariant& data)
    {
        throw std::logic_error("Column " + getTitle().c_str() + "isNotEditable");
    }
};

template <typename ESXRecordT>
struct NestedParentColumn : public Column<ESXRecordT>
{
    NestedParentColumn(int id, int flags, bool fixedRows = false) :
        Column<ESXRecordT>(id, BaseColumn::Display_NestedHeader, flags),
        fixedRows(fixedRows)
    {

    }

    virtual void set(Record<ESXRecordT>& record, const QVariant& data)
    {

    }

    virtual QVariant get(const Record<ESXRecordT>& record) const
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