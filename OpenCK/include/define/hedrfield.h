#ifndef HEDRFIELD_H
#define HEDRFIELD_H

#include "fieldparent.h"
#include <stdint.h>

namespace Define
{
    class HEDRField;
}

struct HEDRData
{
    float version;
    int32_t numRecords;
    uint64_t nextObjectId;
};

typedef struct HEDRData HEDRData;

class HEDRField : public FieldParent
{
public:
    HEDRField();
    HEDRData entries;
};

#endif // HEDRFIELD_H
