#ifndef BASECOLLECTION_H
#define BASECOLLECTION_H

#include <QVector>

class BaseRecord;

class BaseCollection
{
public:
    BaseCollection();
    virtual ~BaseCollection();

    virtual int size() const = 0;

    virtual QString getId(int index) const = 0;
    virtual int getIndex(const QString& id) const = 0;
    virtual int searchId(const QString& id) const = 0;
    virtual QVector<QString> getIdList(bool listDeleted = true) const = 0;

    virtual void replace(int index, const BaseRecord& record) = 0;
    // virtual void appendRecord(const BaseRecord& record) = 0;

    virtual const BaseRecord& getRecord(int index) const = 0;
    virtual const BaseRecord& getRecord(const QString& id) const = 0;

private:
    // Not implemented
    BaseCollection(const BaseCollection&);
    BaseCollection& operator=(const BaseCollection&);
};

#endif // BASECOLLECTION_H
