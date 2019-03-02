#include "messageboxhelper.h"

#include <QMessageBox>

void msgBoxCritical(const QString& msg)
{
    QMessageBox errBox;
    errBox.setText(msg);
    errBox.setIcon(QMessageBox::Icon::Critical);
    errBox.exec();
}
