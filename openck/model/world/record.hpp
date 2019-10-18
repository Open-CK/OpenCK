#ifndef RECORD_H
#define RECORD_H

#include <memory>
#include <stdexcept>

enum State
{
	State_Base = 0,         // Base record (in parent master)
	State_Modified,         // Modified record (defined in master, modified in plugin)
	State_ModifiedOnly,     // Modified record (defined in plugin)
	State_Deleted           // Deleted record
};

class BaseRecord
{
public:
    State state;

    virtual ~BaseRecord();

    virtual BaseRecord* clone() = 0;
    virtual void assign(const BaseRecord& record) = 0;

    bool isDeleted() const;
};

template<typename ESXRecord>
class Record : public BaseRecord
{
public:
	Record();
	Record(State inState, ESXRecord* base = nullptr, ESXRecord* modified = nullptr);
	
	ESXRecord& get();
	const ESXRecord& get() const;

	BaseRecord* clone() override;
	void assign(const BaseRecord& record) override;

	void setModified(const ESXRecord& modified);

    ESXRecord baseRecord;
    ESXRecord modifiedRecord;
};

template<typename ESXRecord>
Record<ESXRecord>::Record()
	: baseRecord(), modifiedRecord()
{
}

template<typename ESXRecord>
Record<ESXRecord>::Record(State inState, ESXRecord* base, ESXRecord* modified)
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

template<typename ESXRecord>
ESXRecord& Record<ESXRecord>::get()
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

template<typename ESXRecord>
const ESXRecord& Record<ESXRecord>::get() const
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

template<typename ESXRecord>
BaseRecord* Record<ESXRecord>::clone()
{
	return new Record<ESXRecord>(*this);
}

template<typename ESXRecord>
void Record<ESXRecord>::assign(const BaseRecord& record)
{
	*this = dynamic_cast<const Record<ESXRecord>&>(record);
}

template<typename ESXRecord>
void Record<ESXRecord>::setModified(const ESXRecord& modified)
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

#endif // RECORD_H
