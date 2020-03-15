#ifndef VIEWMEDIATOR_H
#define VIEWMEDIATOR_H

#include "doc/loader.hpp"
#include "window/datadialog.hpp"
#include "window/mainwindow.hpp"
#include "model/doc/documentmediator.hpp"

#include <QObject>

#include <memory>

class Document;

class ViewMediator : public QObject
{
    Q_OBJECT

public:
    ViewMediator(DocumentMediator& docMed);
    ~ViewMediator();

    void setUpDataDialog(const QString& path);

public slots:
    void showDataDialog();
    void dataDialogAccepted(const QStringList& files, const QString& path, bool isNew);
    void showSaveDialog();

private:
    std::unique_ptr<MainWindow> w;
    std::unique_ptr<DataDialog> dataDlg;

    DocumentMediator& docMed;
    LoaderView loader;

    QString dataPath;

signals:
    void addDocument(const QStringList& files, const QString& path, bool isNew);
    void saveDocument(const QString& path);
};

#endif //VIEWMEDIATOR_H
