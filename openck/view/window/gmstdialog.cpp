#include "gmstdialog.hpp"
#include "../../../ui/ui_gmstdialog.h"

#include "../world/enumdelegate.hpp"
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

    QVector<QPair<int, QString>> modifiedValues;
    modifiedValues.push_back(QPair<int, QString>(0, "Base"));
    modifiedValues.push_back(QPair<int, QString>(1, "Modified"));
    modifiedValues.push_back(QPair<int, QString>(2, "Modified Only"));
    modifiedValues.push_back(QPair<int, QString>(3, "Deleted"));
    modifiedValues.push_back(QPair<int, QString>(4, "Erased"));

    QVector<QPair<int, QString>> varTypeValues;
    varTypeValues.push_back(QPair<int, QString>(1, "Short"));
    varTypeValues.push_back(QPair<int, QString>(2, "Integer"));
    varTypeValues.push_back(QPair<int, QString>(3, "Long"));
    varTypeValues.push_back(QPair<int, QString>(4, "Float"));
    varTypeValues.push_back(QPair<int, QString>(5, "String"));
    varTypeValues.push_back(QPair<int, QString>(6, "Boolean"));

    EnumDelegate* varTypeDelegate = new EnumDelegate(varTypeValues, *document, model);
    EnumDelegate* modifiedDelegate = new EnumDelegate(modifiedValues, *document, model);

    ui->tableView->setItemDelegateForColumn(1, modifiedDelegate);
    ui->tableView->setItemDelegateForColumn(2, varTypeDelegate);

    show();
}
