#include "gmstdialog.hpp"
#include "../../../ui/ui_gmstdialog.h"

#include "../world/enumdelegate.hpp"
#include "../world/variantdelegate.hpp"
#include "../../model/world/ckid.hpp"
#include "../../model/doc/document.hpp"
#include "../../../files/esm/variant.hpp"

#include <QAbstractItemModel>
#include <QPair>
#include <QVector>

GmstDialog::GmstDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::gmstdialog)
{
    ui->setupUi(this);

    enumFactory = std::make_unique<EnumDelegateFactory>(ColumnId::ColumnId_Modification);
    varTypeFactory = std::make_unique<VariantDelegateFactory>();
}

GmstDialog::~GmstDialog()
{
    delete ui;
}

void GmstDialog::setUp(Document* document)
{
    QAbstractItemModel* model = document->getData().getTableModel(CkId::Type_Gmst);

    ui->tableView->setModel(model);

    int last = ui->tableView->horizontalHeader()->count() - 1;
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->resizeRowsToContents();

    varTypeDelegate.reset(varTypeFactory->makeDelegate(*document, this));

    modifiedDelegate.reset(enumFactory->makeDelegate(*document, this));

    ui->tableView->setItemDelegateForColumn(1, modifiedDelegate.get());
    ui->tableView->setItemDelegateForColumn(2, varTypeDelegate.get());

    show();
}
