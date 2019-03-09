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

    void setPaths(const FilePaths& filePaths);

public slots:
    void newFile(const QStringList& files);
    void openFile(const QStringList& files, bool isNew);

private:
    QVector<std::shared_ptr<Document>> documents;
    FilePaths paths;
};

#endif // DOCUMENTMEDIATOR_H
