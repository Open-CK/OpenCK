#ifndef VIEWMEDIATOR_H
#define VIEWMEDIATOR_H

#include "window/datadialog.h"
#include "window/mainwindow.h"

#include <QObject>

#include <memory>

class ViewMediator : public QObject
{
    Q_OBJECT

public:
    ViewMediator();
    ~ViewMediator();

    void setUpDataDialog(const QString& path);

public slots:
    void showDataDialog();
    void dataDialogAccepted(QStringList files, bool isNew);
    void showSaveDialog();

private:
    std::unique_ptr<MainWindow> w;
    std::unique_ptr<DataDialog> dataDlg;
    QString dataPath;

signals:
    void newDocument(QStringList files);
    void openDocument(QStringList files, bool isNew);
    void saveDocument(QString path);
};

#endif //VIEWMEDIATOR_H