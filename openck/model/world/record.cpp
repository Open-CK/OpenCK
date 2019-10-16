#include "record.hpp"

BaseRecord::~BaseRecord()
{
}

bool BaseRecord::isDeleted() const
{
    return state == State_Deleted;
}
