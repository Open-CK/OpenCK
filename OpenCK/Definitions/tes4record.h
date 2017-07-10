#ifndef TES4RECORD_H
#define TES4RECORD_H

#include <stdint.h>
#include "Definitions/recordparent.h"
#include "Definitions/tes4data.h"

namespace Definitions
{
    class TES4Record;
}

class TES4Record : RecordParent
{
public:
    TES4Record();
    TES4Data data;
};

#endif // TES4RECORD_H
