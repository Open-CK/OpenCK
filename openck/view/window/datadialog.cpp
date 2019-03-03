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
    configureTable(dataPath);
    configureList();
}

void DataDialog::newSelection(const QModelIndex& current, const QModelIndex& previous)
{
    FileInfo info = dataTable->getInfoAtSelected(current);
    authorLineEdit()->setText(info.author);
    descriptionTextEdit()->setPlainText(info.description);
}

void DataDialog::configureTable(const QString& dataPath)
{
    dataTable.reset(new DataTable(dataPath));
    tableView()->setModel(dataTable.get());
    tableView()->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView()->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView()->verticalHeader()->hide();
    tableView()->verticalHeader()->setDefaultSectionSize(12);
    tableView()->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView()->horizontalHeader()->setFrameStyle(QFrame::VLine | QFrame::Plain);

    auto selectionModel{ tableView()->selectionModel() };
    connect(selectionModel, &QItemSelectionModel::currentRowChanged,
            this, &DataDialog::newSelection);
}

void DataDialog::configureList()
{
    mastersList.reset(new MastersList());
    mastersView()->setModel(mastersList.get());
    mastersView()->setSelectionMode(QAbstractItemView::NoSelection);
    mastersView()->setStyleSheet(
        "QListView::item:!selected{ border-bottom: 1px solid #CDCDCD; padding: 2px; }"
    );

    connect(dataTable.get(), &DataTable::newFileSelected,
            mastersList.get(), &MastersList::update);
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

QListView* DataDialog::mastersView()
{
    return ui->mastersListView;
}
