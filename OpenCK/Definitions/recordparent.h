#ifndef RECORDPARENT_H
#define RECORDPARENT_H

#include <stdint.h>
#include <array>

namespace Definitions
{
    class RecordParent;
}

class RecordParent
{
public:
    RecordParent();
    virtual ~RecordParent() = 0;
    char* getType();
    uint32_t getDataSize();
    uint32_t getFlags();
    uint32_t getId();
    uint32_t getRevision();
    uint32_t getVersion();
    uint16_t getUnknown();
    uint8_t* getData();
private:
    char type[4];
    uint32_t dataSize;
    uint32_t flags;
    uint32_t id;
    uint32_t revision;
    uint32_t version;
    uint16_t unknown;
    uint8_t data[];
};

#endif // RECORDPARENT_H
