#ifndef FORMHASHMAP_H
#define FORMHASHMAP_H

#include <QHash>
#include <QString>

namespace io
{
    static QHash<quint32, QString> FormHashIndex
    {
        //Add all available Record Types that are supported. Please make sure they are sorted alphabetically for a better overview.
        {'AACT', "Action"},
        {'CLAS', "Class"},
        {'FACT', "Faction"},
        {'GLOB', "Global Variable"},
        {'GMST', "Game Setting"},
        {'GRUP', "Form Group"},
        {'KYWD', "Keyword"},
        {'LCRT', "Location Reference Type"},
        {'TES4', "Plugin info"},
        {'TXST', "Texture Set"},
    };
}

#endif // FORMHASHMAP_H