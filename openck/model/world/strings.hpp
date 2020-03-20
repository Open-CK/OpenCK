#ifndef STRINGS_H
#define STRINGS_H

#include <QString>
#include <QVector>

class Strings
{
public:
    enum Type
    {
        LString,
        ILString,
        DLString,
    };

    Strings();

    QString get(Type type, unsigned int index) const;
    QString set(Type type, unsigned int index, const QString& entry);
    void append(Type type, const QString& entry);
    bool remove(Type type, unsigned int index);
    unsigned int find(Type type, const QString& entry);

private:
    QVector<QString> selectList(Type type) const;

    QVector<QString> strings;
    QVector<QString> ilstrings;
    QVector<QString> dlstrings;
};

#endif // STRINGS_H