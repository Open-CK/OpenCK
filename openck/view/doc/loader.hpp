#ifndef VIEW_LOADER_H
#define VIEW_LOADER_H

#include <QDialog>
#include <QLabel>
#include <QMap>
#include <QProgressBar>
#include <QObject>

class Document;

namespace Ui {
class loaderdialog;
}

class LoaderDialog : public QDialog
{
    Q_OBJECT

public:
    LoaderDialog(QWidget* parent = nullptr);
    ~LoaderDialog();

    void assign(Document* document);
    void nextStage(const QString& name, int records);
    void nextRecord(int records);
    void abort(const QString& error);
    void addMessage(const QString& message) {}

private:
    Document* document;

    bool aborted;
    QString error;
    int totalRecords;
    Ui::loaderdialog* ui;

private slots:
    void cancel();

signals:
    void cancel(Document* document);
    void close(Document* document);
};

class LoaderView : public QObject
{
    Q_OBJECT

    QMap<Document*, LoaderDialog*> documents;

public:
    LoaderView() {}
    virtual ~LoaderView() {}

signals:
    void cancel(Document* document);
    void close(Document* document);

public slots:
    void add(Document* document);
    void loadingStopped(Document* document, bool completed, const QString& error);
    void nextStage(Document* document, const QString& name, int totalRecords);
    void nextRecord(Document* document, int records);
    void loadMessage(Document* document, const QString& message) {}
};

#endif // VIEW_LOADER_H