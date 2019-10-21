#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.hpp"
#include "model/doc/documentmediator.hpp"

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
	void addDocument(const QStringList& files, const QString& savePath, bool isNew);
    void saveDocument(const QString& path);

private:
    QString getDataPath(const QString& applicationName);

    std::unique_ptr<ViewMediator> viewMed;
    std::unique_ptr<DocumentMediator> docMed;

signals:
	void clearFilesSignal();
	void addDocumentSignal(const QStringList& files, const QString& savePath, bool isNew);
    void saveDocumentSignal(const QString& path);
};

#endif // EDITOR_H
