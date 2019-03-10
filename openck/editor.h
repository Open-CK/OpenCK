#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.h"
#include "model/documentmediator.h"

#include <QObject>
#include <QSettings>

#include <memory>

class Editor : public QObject
{
    Q_OBJECT

public:
    Editor(int argc, char *argv[]);
    ~Editor();

public slots:
    void newDocument(const QStringList& files);
    void openDocument(const QStringList& files, bool isNew);
    void saveDocument(const QString& path);

private:
    QString getDataPath(const QString& applicationName);

    std::unique_ptr<ViewMediator> viewMed;
    std::unique_ptr<DocumentMediator> docMed;

signals:
    void newDocumentSignal(const QStringList& files);
    void openDocumentSignal(const QStringList& files, bool isNew);
    void saveDocumentSignal(const QString& path);
};

#endif // EDITOR_H
