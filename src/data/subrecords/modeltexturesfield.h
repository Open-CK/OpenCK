#ifndef MODELTEXTURESFIELD_H
#define MODELTEXTURESFIELD_H

namespace esx
{
    struct ModelTextureHash
    {
        quint32 flags;
        quint32 type;
        quint32 hash;
    };

    struct ModelTextures
    {
        // ??? Seems to be 12 bytes for all records so far... Have to look at it further via CK.
        quint32 headerCount{ 0 };
        quint32 texturesCount{ 0 };
        quint32 unk0{ 0 };

        quint32 uniqueTexturesCount{ 0 };
        quint32 materialsCount{ 0 };

        std::vector<ModelTextureHash> hashes;
    };

    typedef ModelTextureHash ModelTextureHash;
    typedef ModelTextures ModelTextures;
}

#endif