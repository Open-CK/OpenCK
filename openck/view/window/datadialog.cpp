#include "datadialog.h"
#include "../../../ui/ui_datadialog.h"

#include <QDir>

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

void DataDialog::setUp(const QString& dataPath)
{
    dataTable.reset(new DataTable(dataPath));
    tableView()->setModel(dataTable.get());
    tableView()->verticalHeader()->hide();
    tableView()->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView()->horizontalHeader()->setFrameStyle(QFrame::VLine | QFrame::Plain);
}

QTableView* DataDialog::tableView()
{
    return ui->dataTableView;
}
