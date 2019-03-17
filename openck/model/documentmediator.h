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
    void newFile(const QStringList& files, QString author, QString desc);
    void openFile(const QStringList& files, bool isNew, QString author, QString desc);
    void saveFile(const QString& path);

private:
    QVector<std::shared_ptr<Document>> documents;
    FilePaths paths;
};

#endif // DOCUMENTMEDIATOR_H
