#ifndef RECORD_H
#define RECORD_H

#include <memory>
#include <stdexcept>

class BaseRecord
{
public:
    enum State
    {
        State_Active = 0,
        State_Deleted
    };

    State state;

    virtual ~BaseRecord();

    virtual std::shared_ptr<BaseRecord> clone() = 0;
    virtual void assign(const BaseRecord& record) = 0;

    bool isDeleted() const;
};

template<typename ESXRecord>
class Record : public BaseRecord
{
public:
    Record()
        : record()
    {
    }

    Record(State inState, std::shared_ptr<ESXRecord> inRecord = nullptr)
    {
        state = inState;

        if (inRecord && inRecord.get())
        {
            record = inRecord;
        }
    }

    ESXRecord& get()
    {
        if (isDeleted())
        {
            throw std::logic_error("Cannot access a deleted record.");
        }
        else
        {
            return record;
        }
    }

    const ESXRecord& get() const
    {
        if (isDeleted())
        {
            throw std::logic_error("Cannot access a deleted record.");
        }
        else
        {
            return record;
        }
    }

    std::shared_ptr<BaseRecord> clone() override
    {
        return std::make_shared<Record<ESXRecord>>(*this);
    }

    void assign(const BaseRecord& record) override
    {
        *this = dynamic_cast<const Record<ESXRecord>&>(record);
    }

    void setDeleted(bool isDeleted)
    {
        state = isDeleted ? State_Deleted : State_Active;
    }

private:
    ESXRecord record;
};

#endif // RECORD_H
