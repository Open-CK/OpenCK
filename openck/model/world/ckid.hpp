#ifndef CKID_H
#define CKID_H

#include <QString>
#include <QVector>

class CkId
{
public:
    enum ArgumentType
    {
        ArgumentType_None,
        ArgumentType_Id,
        ArgumentType_Index
    };

    enum Type
    {
        Type_None = 0,
        Type_Gmst,
        Type_LoadingLog,
        Type_RunLog,

        NumTypes
    };

    enum { Number = Type_RunLog + 1 };

    CkId(const QString ckid);
    CkId(Type type = Type_None);
    CkId(Type type, const QString& ckid);
    CkId(Type type, int index);

    ArgumentType getArgumentType() const;
    Type getType() const;
    const QString& getId() const;
    int getIndex() const;
    QString getTypeName() const;
    QString toString() const;


    bool equalTo(const CkId& ckid) const;
    bool lessThan(const CkId& ckid) const;

private:
    ArgumentType argumentType;
    Type type;
    QString id;
    int index;
};

bool operator== (const CkId& left, const CkId& right);
bool operator!= (const CkId& left, const CkId& right);
bool operator< (const CkId& left, const CkId& right);

#endif // CKID_H