/*
** datawindow.cpp
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 06-Jul-2017
*/


#include "datawindow.h"
#include "ui_datawindow.h"

/**
 * Constructs a data window with needed information and setup.
 * @brief DataWindow::DataWindow
 * @param parent The parent object of the data window.
 */
DataWindow::DataWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataWindow)
{
    QString path = QCoreApplication::applicationDirPath().append("/");
    workingDir = QDir(path);
    qDebug() << "workingDir set as " << path;
    ui->setupUi(this);
    setWindowTitle("Data");
    setWindowIcon(QIcon(":/openck32x32.png"));
    searchFiles();
}

/**
 * Searches for any ESP or ESM files in the Data directory, then if found will put them in a table.
 * @brief DataWindow::searchFiles
 */
void DataWindow::searchFiles()
{
    QDir dir = workingDir;
    dir.mkdir("Data");  //Note: this won't be called if the directory exists.
    dir.cd("./Data/");

    dir.setNameFilters(QStringList() << "*.esm" << "*.esp");
    QStringList fileList = dir.entryList();

    if (fileList.length() == 0) {
        showFailure();
    } else {
        formatTable(fileList.count(), fileList);
    }
}

/**
 * Formats the table in the Data window with the ESP and ESM files found by #searchFiles()
 * @brief DataWindow::formatTable
 * @param quant The amount of items in the table.
 * @param fileList The list of files from which the ESP and ESM files are shown.
 * @see DataWindow::searchFiles()
 */
void DataWindow::formatTable(int quant, QStringList fileList)
{
    //Set up model headers and format
    QStandardItemModel *model = new QStandardItemModel(quant, 3, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Filename")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Status")));

    QTableView *table = ui->tableView;
    table->setModel(model);

    int half = table->width() / 2;
    int width = table->width();
    table->setColumnWidth(0, 30);
    table->setColumnWidth(1, half);
    table->setColumnWidth(2, (width - half - 30));
    table->verticalHeader()->hide();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStandardItem *check = new QStandardItem();
    check->data(Qt::CheckStateRole);
    check->setCheckState(Qt::Unchecked);

    for (int i = 0; i < quant; i++){
        model->setItem(i, 0, check);
    }

    populateTable(quant, fileList, table);
}
/**
 * Populates a given table with a list of elements.
 * @brief DataWindow::populateTable
 * @param quant The amount of items in the table.
 * @param fileList The list of items (in the case of DataWindow, filenames) from which the table is populated by.
 * @param table The table to be populated.
 * @see DataWindow::formatTable(int,QStringList)
 */
void DataWindow::populateTable(int quant, QStringList fileList, QTableView* table)
{
    //Set up file names and status
    for (int i = 0; i < quant; i++) {
        QString fileName = fileList[i];
        QModelIndex index = table->model()->index(i, 1);
        table->model()->setData(index, fileList[i]);

        QString type = fileName.split(".")[1];
        QString desc = "";
        index = table->model()->index(i, 2);

        if (type.toLower() == "esm") {
            desc = "Master File";
        } else if (type.toLower() == "esp") {
            desc = "Plugin File";
        }

        table->model()->setData(index, desc);
    }
}

/**
 * Creates a message box notifying the user that there were no ESP or ESM files found.
 * @brief DataWindow::showFailure
 */
void DataWindow::showFailure()
{
    QMessageBox *msg = new QMessageBox;
    msg->setSizeIncrement(600, 400);
    msg->setText("No .esm or .esp files were found in the Data folder.");
    msg->setStandardButtons(QMessageBox::Ok);
    msg->setIcon(QMessageBox::Critical);
    msg->setWindowIcon(QIcon(":/openck32x32.png"));
    msg->exec();
}

/**
 * Destructs the data window object by deleting the pointer to the UI file.
 * @brief DataWindow::~DataWindow
 */
DataWindow::~DataWindow()
{
    delete ui;
}

/**
 * Method called from when "Cancel" is pressed on the Data window.
 * @brief DataWindow::on_buttonBox_rejected
 */
void DataWindow::on_buttonBox_rejected()
{
    close();
}
