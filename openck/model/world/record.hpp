#ifndef RECORD_H
#define RECORD_H

#include <memory>
#include <stdexcept>

class BaseRecord
{
public:
    enum State
    {
        State_Base = 0,         // Base record (in parent master)
        State_Modified,         // Modified record (defined in master, modified in plugin)
        State_ModifiedOnly,     // Modified record (defined in plugin)
        State_Deleted           // Deleted record
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
        : baseRecord(), modifiedRecord()
    {
    }

    Record(State inState, std::shared_ptr<ESXRecord> base = nullptr, std::shared_ptr<ESXRecord> modified = nullptr)
    {
        state = inState;

        if (base && base.get())
        {
            baseRecord = base;
        }

        if (modified && modified.get())
        {
            modifiedRecord = modified;
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
            return state == State_Base ? baseRecord : modifiedRecord;
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
            return state == State_Base ? baseRecord : modifiedRecord;
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

    void setModified(std::shared_ptr<ESXRecord> modified)
    {
        if (isDeleted())
        {
            throw std::logic_error("Cannot access a deleted record.");
        }
        else
        {
            modifiedRecord = modified;
        }
    }

private:
    std::shared_ptr<ESXRecord> baseRecord;
    std::shared_ptr<ESXRecord> modifiedRecord;
};

#endif // RECORD_H
