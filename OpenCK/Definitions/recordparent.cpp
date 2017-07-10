#include "recordparent.h"

RecordParent::RecordParent() {}

RecordParent::~RecordParent() {}

char* RecordParent::getType()
{
    return type;
}

uint32_t RecordParent::getDataSize()
{
    return dataSize;
}

uint32_t RecordParent::getFlags()
{
    return flags;
}

uint32_t RecordParent::getId()
{
    return id;
}

uint32_t RecordParent::getRevision()
{
    return revision;
}

uint32_t RecordParent::getVersion()
{
    return version;
}

uint16_t RecordParent::getUnknown()
{
    return unknown;
}

uint8_t* RecordParent::getData()
{
    return data;
}
