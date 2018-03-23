#ifndef BODYTEMPLATEFIELD_H
#define BODYTEMPLATEFIELD_H

namespace esx
{
    struct BodyTemplateField
    {
        enum Version
        {
            BODT,
            BOD2
        };

        Version version{ BODT };
        quint32 bodyPartFlags{ 0 };
        union
        {
            quint32 data{ 0 };
            quint8 bytes[4];
        } flags;
        quint32 skill{ 2 };
    };

    typedef BodyTemplateField BodyTemplateField;
}

#endif