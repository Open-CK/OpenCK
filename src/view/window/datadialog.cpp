#include "datadialog.hpp"
#include "../../../ui/ui_datadialog.h"

#include "../messageboxhelper.hpp"

#include <QDateTime>
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

void DataDialog::setUp(const QString& path)
{
    dataPath = path;
    configureTable();
    configureList();
}

void DataDialog::newSelection(const QModelIndex& current, const QModelIndex& previous)
{
    FileInfo info = dataTable->getInfoAtSelected(current);
    authorLineEdit()->setText(info.author);
    descriptionTextEdit()->setPlainText(info.description);

    if (info.flags.test(FileFlag::Master) || info.flags.test(FileFlag::LightMaster))
    {
        authorLineEdit()->setEnabled(false);
        descriptionTextEdit()->setEnabled(false);
        activeButton()->setEnabled(false);
    }
    else
    {
        authorLineEdit()->setEnabled(true);
        descriptionTextEdit()->setEnabled(true);
        activeButton()->setEnabled(true);
    }

    QFileInfo dateInfo{ dataPath + "/" + info.fileName };
    createdLabel()->setText(
        QString("Created On: %1").arg(
            dateInfo.created().toString("dd/MM/yy hh:mm AP")
        )
    );
    modifiedLabel()->setText(
        QString("Modified On: %1").arg(
            dateInfo.lastModified().toString("dd/MM/yy hh:mm AP")
        )
    );
}

void DataDialog::configureTable()
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

    connect(tableView(), &QTableView::doubleClicked,
            dataTable.get(), &DataTable::doubleClicked);
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

void DataDialog::accept()
{
    auto files = dataTable->getFiles();
    
    QStringList fileNames = std::get<0>(files);
    int active = std::get<1>(files);
    bool isNew = false;
    QString savePath;

    if (active == -1)
    {
        isNew = true;
        savePath = "";
    }
    else
    {
        savePath = fileNames.at(active);
    }

    this->close();
    
    emit addDocument(fileNames, savePath, isNew);
}

void DataDialog::on_activeButton_clicked()
{
    dataTable->setActive(tableView()->selectionModel()->currentIndex());
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

QLabel* DataDialog::createdLabel()
{
    return ui->createdLabel;
}

QLabel* DataDialog::modifiedLabel()
{
    return ui->modifiedLabel;
}

QPushButton* DataDialog::activeButton()
{
    return ui->activeButton;
}
