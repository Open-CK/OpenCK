#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>

namespace Ui {
class datadialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = nullptr);
    ~DataDialog();

private:
    Ui::datadialog *ui;
};

#endif // DATADIALOG_H
