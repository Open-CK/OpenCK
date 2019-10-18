#ifndef IDCOLLECTION_HPP
#define IDCOLLECTION_HPP

#include "../../../files/esm/esmreader.hpp"
#include "collection.hpp"

template<typename ESXRecord, typename IdAccessorT = IdAccessor<ESXRecord>>
class IdCollection : public Collection<ESXRecord, IdAccessorT>
{
public:
	int load(ESMReader& esm, bool base);
	int load(const ESXRecord& record, int index, bool base);

private:
	virtual void loadRecord(ESXRecord& record, ESMReader& reader);
};

template<typename ESXRecord, typename IdAccessorT>
void IdCollection<ESXRecord, IdAccessorT>::loadRecord(ESXRecord& record, ESMReader& reader)
{
	record.load(reader);
}

template<typename ESXRecord, typename IdAccessorT>
int IdCollection<ESXRecord, IdAccessorT>::load(const ESXRecord& record, int index, bool base)
{
	if (index == -1)
	{
		Record<ESXRecord> rec;
		rec.state = base ? State::State_Base : State::State_ModifiedOnly;
		(base ? rec.baseRecord : rec.modifiedRecord) = record;

		index = this->size();
		appendRecord(rec);
	}

	return index;
}

template<typename ESXRecord, typename IdAccessorT>
int IdCollection<ESXRecord, IdAccessorT>::load(ESMReader& reader, bool base)
{
	ESXRecord record;
	loadRecord(record, esm);

	QString id = IdAccessorT().getId(record);
	int index = searchId(id);

	return load(record, index, base);
}

#endif // IDCOLLECTION_HPP
