#ifndef IDCOLLECTION_HPP
#define IDCOLLECTION_HPP

#include "../../../files/esm/esmreader.hpp"
#include "collection.hpp"

template<typename ESXRecord, typename IdAccessorT = IdAccessor<ESXRecord>>
class IdCollection : public Collection<ESXRecord, IdAccessorT>
{
public:
    int load(ESMReader& esm)
    {
        ESXRecord record;
        loadRecord(record, esm);

        QString id = IdAccessorT().getId(record);
        int index = searchId(id);

        return load(record, esm, index);
    }

    int load(ESXRecord& record, bool base, int index)
    {
        return 0;
    }

private:
    void loadRecord(ESXRecord& record, ESMReader& reader)
    {
        record.load(reader);
    }
};

#endif // IDCOLLECTION_HPP
