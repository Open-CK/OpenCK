#include "strings.hpp"

Strings::Strings()
{

}

QString Strings::get(Type type, unsigned int index) const
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() > index)
    {
        return QString("");
    }
    else
    {
        return stringlist[index];
    }
}

QString Strings::set(Type type, unsigned int index, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() <= index)
    {
        stringlist[index] = entry;
    }
}

void Strings::append(Type type, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    stringlist.push_back(entry);
}

bool Strings::remove(Type type, unsigned int index)
{
    QVector<QString> stringlist = selectList(type);

    if (stringlist.size() <= index)
    {
        stringlist.remove(index);
    
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int Strings::find(Type type, const QString& entry)
{
    QVector<QString> stringlist = selectList(type);

    return stringlist.indexOf(entry);
}

QVector<QString> Strings::selectList(Type type) const
{
    switch (type)
    {
        case Type::LString:
        {
            return strings;
        }
        case Type::ILString:
        {
            return ilstrings;
        }
        case Type::DLString:
        {
            return dlstrings;
        }
    }
}
