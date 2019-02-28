#include "datadialog.h"

#include "../../../ui/ui_datadialog.h"

DataDialog::DataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::datadialog)
{
    ui->setupUi(this);
}

DataDialog::~DataDialog()
{
    delete ui;
}
