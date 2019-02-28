#include "viewmediator.h"

#include "window/datadialog.h"

ViewMediator::ViewMediator()
{   
    w.reset(new MainWindow());

    QObject::connect(w.get(), &MainWindow::actionData_triggered, this, &ViewMediator::showDataDialog);

    w->show();
}

ViewMediator::~ViewMediator()
{

}

void ViewMediator::showDataDialog()
{
    DataDialog dlg;
    dlg.setWindowFlags(dlg.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dlg.exec();
}
