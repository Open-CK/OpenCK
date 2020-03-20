#ifndef STRINGS_H
#define STRINGS_H

#include "../files/filepaths.hpp"

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

        NumTypes
    };

    Strings();

    void load(QString filename, const FilePaths& paths);

    QString get(Type type, unsigned int index) const;
    bool set(Type type, unsigned int index, const QString& entry);
    unsigned int append(Type type, const QString& entry);
    bool remove(Type type, unsigned int index);
    unsigned int find(Type type, const QString& entry);

private:
    QString typeExtensions[NumTypes]
    {
        "STRINGS",
        "ILSTRINGS",
        "DLSTRINGS"
    };

    void loadLStrings(QFile& file);
    void loadILStrings(QFile& file);
    void loadDLStrings(QFile& file);

    unsigned int readHeader(QFile& file);

    QVector<QString> selectList(Type type) const;

    QVector<QString> strings;
    QVector<QString> ilstrings;
    QVector<QString> dlstrings;

    struct DirectoryEntry
    {
        int id;
        int offset;
    };
};

#endif // STRINGS_H