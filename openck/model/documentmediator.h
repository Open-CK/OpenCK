#ifndef DOCUMENTMEDIATOR_H
#define DOCUMENTMEDIATOR_H

#include "../files/filepaths.h"

#include "document.h"

#include <QObject>
#include <QVector>

#include <memory>

class Document;

class DocumentMediator : public QObject
{
    Q_OBJECT

public:
    DocumentMediator();
    ~DocumentMediator();

    void addDocument(const QStringList& files, const QString& savePath, bool isNew);
    void setPaths(const FilePaths& filePaths);

private:
    QVector<std::shared_ptr<Document>> documents;
    FilePaths paths;
};

#endif // DOCUMENTMEDIATOR_H
