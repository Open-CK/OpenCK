#include "record.h"

BaseRecord::~BaseRecord()
{
}

bool BaseRecord::isDeleted() const
{
    return state == State_Deleted;
}
