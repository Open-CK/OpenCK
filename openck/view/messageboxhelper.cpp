#include "messageboxhelper.h"

#include <QMessageBox>

void msgBoxCritical(const QString& msg)
{
    QMessageBox errBox;
    errBox.setText(msg);
    errBox.setIcon(QMessageBox::Icon::Critical);
    errBox.exec();
}

void msgBoxAlert(const QString& msg)
{
    QMessageBox alertBox;
    alertBox.setText(msg);
    alertBox.setIcon(QMessageBox::Icon::Warning);
    alertBox.exec();
}
