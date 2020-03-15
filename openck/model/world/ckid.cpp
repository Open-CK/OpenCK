#include "ckid.hpp"

#include <sstream>
#include <stdexcept>

struct TypeData
{
    CkId::Type type;
    const char* name;
};

static const TypeData typesIdArg[] =
{
    { CkId::Type_None, 0 }
};

static const TypeData typesNoArg[] =
{
    { CkId::Type_RunLog, "Runtime Error Log" },
    { CkId::Type_None, 0 }
};

static const TypeData typesIndexArg[] =
{
    { CkId::Type_LoadingLog, "Loading Error Log" },
    { CkId::Type_None, 0 }
};

CkId::CkId(const QString ckid) :
    index(0), argumentType(ArgumentType_None), type(Type_None)
{
    QString::size_type index = ckid.indexOf(':');

    if (index != -1)
    {
        QString type_ = ckid.mid(0, index);

        for (int i = 0; typesIdArg[i].name; ++i)
        {
            if (type_ == typesIdArg[i].name)
            {
                argumentType = ArgumentType_Id;
                type = typesIdArg[i].type;
                id = ckid.mid(index+1, ckid.size());
                return;
            }
        }

        for (int i = 0; typesIndexArg[i].name; ++i)
        {
            if (type_ == typesIndexArg[i].name)
            {
                argumentType = ArgumentType_Index;
                type = typesIndexArg[i].type;
                id = ckid.mid(index + 1, ckid.size());
                return;
            }
        }
    }
    else
    {
        for (int i = 0; typesNoArg[i].name; ++i)
        {
            if (ckid == typesNoArg[i].name)
            {
                argumentType = ArgumentType_None;
                type = typesNoArg[i].type;
                id = ckid.mid(index + 1, ckid.size());
                return;
            }
        }
    }
}

CkId::CkId(Type type) :
    index(0), argumentType(ArgumentType_None), type(type)
{
    for (int i = 0; typesIdArg[i].name; ++i)
    {
        if (type == typesIdArg[i].type)
        {
            argumentType = ArgumentType_Id;
            return;
        }
    }

    for (int i = 0; typesIndexArg[i].name; ++i)
    {
        if (type == typesIndexArg[i].type)
        {
            argumentType = ArgumentType_Index;
            return;
        }
    }
}

CkId::CkId(Type type, const QString& id) :
    index(0), argumentType(ArgumentType_Id), type(type), id(id)
{
}

CkId::CkId(Type type, int index) :
    index(index), argumentType(ArgumentType_Index), type(type)
{
}

CkId::ArgumentType CkId::getArgumentType() const
{
    return argumentType;
}

CkId::Type CkId::getType() const
{
    return type;
}

const QString& CkId::getId() const
{
    if (argumentType != ArgumentType_Id)
    {
        throw std::runtime_error("Invalid access of ID from CKID with no ID");
    }

    return id;
}

int CkId::getIndex() const
{
    if (argumentType != ArgumentType_Index)
    {
        throw std::runtime_error("Invalid access of index from CKID with no index");
    }

    return index;
}

bool CkId::equalTo(const CkId& ckid) const
{
    if (argumentType != ckid.argumentType || type != ckid.type)
    {
        return false;
    }

    switch (argumentType)
    {
    case (ArgumentType_Id):
    {
        return id == ckid.id;
    }
    case (ArgumentType_Index):
    {
        return index == ckid.index;
    }
    default:
    {
        return true;
    }
    }
}

bool CkId::lessThan(const CkId& ckid) const
{
    if (type < ckid.type)
    {
        return true;
    }
    if (type > ckid.type)
    {
        return false;
    }

    switch (argumentType)
    {
    case (ArgumentType_Id):
    {
        return id < ckid.id;
    }
    case (ArgumentType_Index):
    {
        return index < ckid.index;
    }
    default:
    {
        return false;
    }
    }
}

QString CkId::getTypeName() const
{
    const TypeData* typeData = typesNoArg;

    if (argumentType == ArgumentType_Id)
    {
        typeData = typesIdArg;
    }
    else if (argumentType == ArgumentType_Index)
    {
        typeData = typesIndexArg;
    }

    for (int i = 0; typeData[i].name; ++i)
    {
        if (typeData[i].type == type)
        {
            return typeData[i].name;
        }
    }

    throw std::runtime_error("Failed to get CKID type name");
}

QString CkId::toString() const
{
    std::ostringstream str;
    str << getTypeName().toStdString();

    switch (argumentType)
    {
    case ArgumentType_None:        break;
    case ArgumentType_Id:        str << ": " << id.toStdString(); break;
    case ArgumentType_Index:    str << ": " << index; break;
    }

    return QString(str.str().c_str());
}

bool operator== (const CkId& left, const CkId& right)
{
    return left.equalTo(right);
}

bool operator!= (const CkId& left, const CkId& right)
{
    return !left.equalTo(right);
}

bool operator< (const CkId& left, const CkId& right)
{
    return left.lessThan(right);
}