#include "gmstdialog.hpp"
#include "../../../ui/ui_gmstdialog.h"

#include "../../model/world/ckid.hpp"
#include "../../model/doc/document.hpp"

#include <QAbstractItemModel>

GmstDialog::GmstDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::gmstdialog)
{
    ui->setupUi(this);
}

GmstDialog::~GmstDialog()
{
    delete ui;
}

void GmstDialog::setUp(Document* document)
{
    QAbstractItemModel* model = document->getData().getTableModel(CkId::Type_Gmst);

    ui->tableView->setModel(model);

    show();
}
