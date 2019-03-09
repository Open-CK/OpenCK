#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>

class Document : public QObject
{
    Q_OBJECT

public:
    Document(const QStringList& files, bool isNew);
    ~Document();

    void load(const QString& fileName);
    void save();

    bool isNewFile();

private:
    void createBase();

    QStringList derivedFiles;
    QString savePath;
    bool newFile;
};

#endif // DOCUMENT_H
