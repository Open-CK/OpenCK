#ifndef OBJECTBOUNDSFIELD_H
#define OBJECTBOUNDSFIELD_H

#include "reader.h"

namespace esx
{
    struct ObjectBoundsField
    {
        quint16 xmin;
        quint16 ymin;
        quint16 zmin;
        quint16 xmax;
        quint16 ymax;
        quint16 zmax;
    };

    typedef ObjectBoundsField ObjectBoundsField;
}

#endif // OBJECTBOUNDSFIELD_H
