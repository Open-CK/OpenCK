#ifndef FORMHASHMAP_H
#define FORMHASHMAP_H

#include <QHash>
#include <QString>

namespace io
{
    static QHash<quint32, QString> FormHashIndex
    {
        //Add all available Record Types that are supported. Please make sure they are sorted alphabetically for a better overview.
        {'AACT', "AACT"},
        {'CLAS', "CLAS"},
        {'GLOB', "GLOB"},
        {'GMST', "GMST"},
        {'GRUP', "GRUP"},
        {'KYWD', "KYWD"},
        {'LCRT', "LCRT"},
        {'TES4', "TES4"},
        {'TXST', "TXST"},
    };
}

#endif // FORMHASHMAP_H