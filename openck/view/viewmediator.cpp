#include "viewmediator.h"

ViewMediator::ViewMediator()
{   
    w.reset(new MainWindow());

    QObject::connect(w.get(), &MainWindow::actionData_triggered, this, &ViewMediator::showDataDialog);

    w->show();
}

ViewMediator::~ViewMediator()
{

}

void ViewMediator::setUpDataDialog(const QString& dataPath)
{
    dataDlg.reset(new DataDialog());
    dataDlg->setWindowFlags(dataDlg->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dataDlg->setUp(dataPath);
}

void ViewMediator::showDataDialog()
{
    dataDlg->exec();
}
