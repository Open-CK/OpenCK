#ifndef DOCUMENTMEDIATOR_H
#define DOCUMENTMEDIATOR_H

#include "document.hpp"
#include "loader.hpp"
#include "../../../files/filepaths.hpp"

#include <QThread>
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
    void clearFiles();
    void addDocument(const QStringList& files, const QString& savePath, bool isNew);
    Document* makeDocument(const QStringList& files, const QString& savePath, bool isNew);
    void insertDocument(Document* document);
    void saveFile(const QString& path);
    void removeDocument(Document* document);

signals:
    void loadRequest(Document* document);
    void nextStage(Document* document, const QString& name, int records);
    void nextRecord(Document* document, int records);
    void loadingStopped(Document* document, bool completed, const QString& error);
    void loadMessage(Document* document, const QString& message);
    void cancelLoading(Document* document);

private slots:
    void documentLoaded(Document* document);
    void documentNotLoaded(Document* document, const QString& error);

private:
    QVector<std::shared_ptr<Document>> documents;
    QThread loaderThread;
    Loader loader;
    
    FilePaths paths;
};

#endif // DOCUMENTMEDIATOR_H