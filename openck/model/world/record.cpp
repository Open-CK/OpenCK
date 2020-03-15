#include "record.hpp"

BaseRecord::~BaseRecord()
{
}

bool BaseRecord::isDeleted() const
{
    return state == State_Deleted || state == State_Erased;
}

bool BaseRecord::isErased() const
{
	return state == State_Erased;
}

bool BaseRecord::isModified() const
{
	return state == State_Modified || state == State_ModifiedOnly;
}
