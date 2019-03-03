#include "viewmediator.h"

#include <QFileDialog>

ViewMediator::ViewMediator()
{   
    w.reset(new MainWindow());

    QObject::connect(w.get(), &MainWindow::actionData_triggered, this, &ViewMediator::showDataDialog);
    QObject::connect(w.get(), &MainWindow::actionSave_triggered, this, &ViewMediator::showSaveDialog);

    w->show();
}

ViewMediator::~ViewMediator()
{

}

void ViewMediator::setUpDataDialog(const QString& path)
{
    dataPath = path;
    dataDlg.reset(new DataDialog());
    dataDlg->setWindowFlags(dataDlg->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dataDlg->setUp(path);
}

void ViewMediator::showDataDialog()
{
    dataDlg->exec();
}

void ViewMediator::showSaveDialog()
{
    QFileDialog saveDialog;
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setModal(true);
    saveDialog.setNameFilter("*.esp");
    saveDialog.setDirectory(dataPath);
    saveDialog.exec();
}
