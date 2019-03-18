#ifndef COLLECTION_H
#define COLLECTION_H

#include "basecollection.h"
#include "record.h"

#include <QMap>
#include <QVector>

const int NOT_FOUND = -1;

template<typename ESXRecord>
struct IdAccessor
{
    void setId(ESXRecord& record, const QString& id)
    {
        record.id = id;
    }

    QString getId(ESXRecord& record)
    {
        return record.id;
    }
};

template<typename ESXRecord, typename IdAccessorT = IdAccessor<ESXRecord>>
class Collection : public BaseCollection
{
public:
    Collection()
    {
    }

    virtual ~Collection() override
    {
    }

    int size() const override
    {
        return records.size();
    }

    QString getId(int index) const override
    {
        return IdAccessorT().getId(records.at(index).get());
    }

    int getIndex(const QString& id) const override
    {
        int index = searchId(id);

        if (index == NOT_FOUND)
        {
            throw std::runtime_error("Invalid id: " + id.toStdString());
        }
        else
        {
            return index;
        }
    }

    int searchId(const QString& id) const override
    {
        QString lowerId = id.toLower();
        QMap<QString, int>::const_iterator it = index.find(lowerId);

        if (it == index.end())
        {
            return NOT_FOUND;
        }
        else
        {
            return it.value();
        }
    }

    QVector<QString> getIdList(bool listDeleted = true) const override
    {
        QVector<QString> ids;

        for (QMap<QString, int>::const_iterator it = index.begin(); it != index.end(); ++it)
        {   
            if (listDeleted || !records[it.value()].isDeleted())
            {
                ids.push_back(IdAccessorT().getId(records[it.value()].get()));
            }
        }

        return ids;
    }

    void replace(int index, const BaseRecord& record) override
    {
        records.at(index) = dynamic_cast<const Record<ESXRecord>&>(record);
    }

    void appendRecord(const BaseRecord& record) override
    {
    }

    const BaseRecord& getRecord(int index) const override
    {
        return records.at(index);
    }

    const BaseRecord& getRecord(const QString& id) const override
    {
        int index = getIndex(id);
        return records.at(index);
    }

private:
    QVector<ESXRecord> records;
    QMap<QString, int> index;

    // Not implemented
    Collection(const Collection&);
    Collection& operator=(const Collection&);
};

#endif // COLLECTION_H
