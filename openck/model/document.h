#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>

class Document : public QObject
{
    Q_OBJECT

public:
    Document(const QStringList& files, const QString& fileSavePath, bool isNew);
    ~Document();

    bool isNewFile();
    void save();

private:
    void createEmpty();

    QStringList derivedFiles;
    QString savePath;
    bool newFile;
};

#endif // DOCUMENT_H
