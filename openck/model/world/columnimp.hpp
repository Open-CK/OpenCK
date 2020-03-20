#ifndef COLUMNIMP_H
#define COLUMNIMP_H

#include "basecolumn.hpp"
#include "columns.hpp"
#include "../../../files/esm/variant.hpp"

#include <QVariant>

template<typename ESXRecord>
struct FloatColumn : public Column<ESXRecord>
{
    FloatColumn() :
        Column<ESXRecord>(ColumnId::ColumnId_Value, BaseColumn::Display_Float)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        return record.get().value.getFloat();
    }

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {
        ESXRecord newRecord = record.get();
        newRecord.value.setFloat(data.toFloat());
        record.setModified(newRecord);
    }

    virtual bool isEditable() const
    {
        return true;
    }
};

template<typename ESXRecord>
struct StringIdColumn : public Column<ESXRecord>
{
    StringIdColumn(bool hidden = false) :
        Column<ESXRecord>(ColumnId::ColumnId_Id, BaseColumn::Display_Id,
            hidden ? 0 : BaseColumn::Flag_Table | BaseColumn::Flag_Dialogue)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        return record.get().id;
    }

    virtual bool isEditable() const
    {
        return false;
    }
};

template<typename ESXRecord>
struct RecordStateColumn : public Column<ESXRecord>
{
    RecordStateColumn() :
        Column<ESXRecord>(ColumnId::ColumnId_Modification, BaseColumn::Display_RecordState)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        if (record.state == State::State_Erased)
        {
            return static_cast<int>(State::State_Deleted);
        }

        return static_cast<int>(record.state);
    }

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {
        record.state = static_cast<State>(data.toInt());
    }

    virtual bool isEditable() const
    {
        return true;
    }

    virtual bool isUserEditable() const
    {
        return false;
    }
};

template<typename ESXRecord>
struct FixedRecordTypeColumn : public Column<ESXRecord>
{
    int type;

    FixedRecordTypeColumn(int type) :
        Column<ESXRecord>(ColumnId::ColumnId_RecordType, BaseColumn::Display_SignedInteger32, 0),
        type(type)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        return type;
    }

    virtual bool isEditable() const
    {
        return false;
    }
};

template<typename ESXRecord>
struct VarTypeColumn : public Column<ESXRecord>
{
    VarTypeColumn(BaseColumn::Display display) :
        Column<ESXRecord>(ColumnId::ColumnId_ValueType, display, BaseColumn::Flag_Table | BaseColumn::Flag_Dialogue)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        return static_cast<int>(record.get().value.getType());
    }

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {
        ESXRecord newRecord = record.get();
        newRecord.value.setType(static_cast<VariantType>(data.toInt()));
        record.setModified(newRecord);
    }

    virtual bool isEditable() const
    {
        return true;
    }
};

template<typename ESXRecord>
struct VarValueColumn : public Column<ESXRecord>
{
    VarValueColumn() :
        Column<ESXRecord>(ColumnId::ColumnId_Value, BaseColumn::Display_Var, BaseColumn::Flag_Table | BaseColumn::Flag_Dialogue)
    {

    }

    virtual QVariant get(const Record<ESXRecord>& record) const
    {
        switch (record.get().value.getType())
        {
            case VariantType::Var_String:
                return record.get().value.getString();
        
            case VariantType::Var_Int:
            case VariantType::Var_Short:
            case VariantType::Var_Long:
                return record.get().value.getInt();

            case VariantType::Var_Float:
                return record.get().value.getFloat();

            default:
                return QVariant();
        }
    }

    virtual void set(Record<ESXRecord>& record, const QVariant& data)
    {
        ESXRecord newRecord = record.get();

        switch (newRecord.value.getType())
        {
            case VariantType::Var_String:
                newRecord.value.setString(data.toString());
                break;

            case VariantType::Var_Int:
            case VariantType::Var_Short:
            case VariantType::Var_Long:
                newRecord.value.setInt(data.toInt());
                break;

            case VariantType::Var_Float:
                newRecord.value.setFloat(data.toFloat());
                break;

            default:
                break;
        }

        record.setModified(newRecord);
    }

    virtual bool isEditable() const
    {
        return true;
    }
};

#endif // COLUMNIMP_H