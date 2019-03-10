#include "viewmediator.h"

#include <QFileDialog>

ViewMediator::ViewMediator()
{   
    w.reset(new MainWindow());

    connect(w.get(), &MainWindow::actionData_triggered, this, &ViewMediator::showDataDialog);
    connect(w.get(), &MainWindow::actionSave_triggered, this, &ViewMediator::showSaveDialog);

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

    connect(dataDlg.get(), &DataDialog::newDocument, this, &ViewMediator::dataDialogAccepted);
}

void ViewMediator::showDataDialog()
{
    dataDlg->exec();
}

void ViewMediator::dataDialogAccepted(QStringList files, bool isNew)
{
    if (isNew)
    {
        emit newDocument(files);
    }
    else
    {
        emit openDocument(files, isNew);
    }
}

void ViewMediator::showSaveDialog()
{
    QFileDialog saveDialog;
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setModal(true);
    saveDialog.setDirectory(dataPath);

    emit saveDocument(saveDialog.getSaveFileName(
        nullptr, "Save Plugin File", "", "Elder Scrolls Plugin fies (*.esp)")
    );
}


