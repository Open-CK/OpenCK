#include "datadialog.h"
#include "../../../ui/ui_datadialog.h"

#include <QDir>
#include <QItemSelectionModel>
#include <QModelIndex>

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
    tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView()->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView()->verticalHeader()->hide();
    tableView()->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView()->horizontalHeader()->setFrameStyle(QFrame::VLine | QFrame::Plain);

    auto selectionModel{ tableView()->selectionModel() };
    connect(selectionModel, &QItemSelectionModel::currentRowChanged,
            this, &DataDialog::newSelection);
}

void DataDialog::newSelection(const QModelIndex& current, const QModelIndex& previous)
{
    FileInfo info = dataTable->getInfoAtSelected(current);
    authorLineEdit()->setText(info.author);
    descriptionTextEdit()->setPlainText(info.description);
}

QTableView* DataDialog::tableView()
{
    return ui->dataTableView;
}

QLineEdit* DataDialog::authorLineEdit()
{
    return ui->authorLineEdit;
}

QPlainTextEdit* DataDialog::descriptionTextEdit()
{
    return ui->descriptionTextEdit;
}

QListView* DataDialog::masterView()
{
    return ui->mastersListView;
}
