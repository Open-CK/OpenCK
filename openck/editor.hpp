#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.hpp"
#include "model/documentmediator.hpp"

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
    void newDocument(const QStringList& files, QString author, QString desc);
    void openDocument(const QStringList& files, bool isNew, QString author, QString desc);
    void saveDocument(const QString& path);

private:
    QString getDataPath(const QString& applicationName);

    std::unique_ptr<ViewMediator> viewMed;
    std::unique_ptr<DocumentMediator> docMed;

signals:
    void newDocumentSignal(const QStringList& files, QString author, QString desc);
    void openDocumentSignal(const QStringList& files, bool isNew, QString author, QString desc);
    void saveDocumentSignal(const QString& path);
};

#endif // EDITOR_H
