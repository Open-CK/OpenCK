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
 * @brief Constructs & sets up the data window.
 * @param parent The parent object of the data window.
 */
DataWindow::DataWindow(QWidget* parent) :
    QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint),
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
 * Searches for any .esm or .esm files in the Data directory, then if found will put them in a table.
 * @brief Searches for .esm and .esp files in the Data directory.
 */
void DataWindow::searchFiles()
{
    workingDir.mkdir("Data");  //Note: this won't be called if the directory exists.
    workingDir.cd("./Data/");
    qDebug() << "dir changed to " << workingDir.absolutePath();

    workingDir.setNameFilters(QStringList() << "*.esm" << "*.esp");
    QStringList fileList = workingDir.entryList();

    if (fileList.length() == 0) {
        showFailure("No .esm or .esp files were found in the Data directory");
    }
    formatListView(fileList.count(), fileList);
}

/**
 * Formats the table in the Data window with the .esp and .esm files found by searchFiles()
 * @brief Formats the table in the data window with .esp and .esm files.
 * @param quant The amount of items in the table.
 * @param fileList The list of files from which the .esp and .esm files are shown.
 * @see DataWindow::searchFiles()
 */
void DataWindow::formatListView(int quant, QStringList fileList)
{
    //Set up model headers and format
    model = new QStandardItemModel(quant, 3, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Filename")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Status")));

    table = ui->fileListView;
    table->setModel(model);

    int half = table->width() / 2;
    int width = table->width();
    table->setColumnWidth(0, 20);
    table->setColumnWidth(1, half);
    table->setColumnWidth(2, (width - half - 20));
    table->verticalHeader()->hide();
    table->horizontalHeader()->setFixedHeight(20);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < quant; i++){
        table->setRowHeight(i, 20);
        QStandardItem *check = new QStandardItem();
        check->data(Qt::CheckStateRole);
        check->setCheckState(Qt::Unchecked);
        check->setFlags(check->flags() | Qt::ItemIsEditable);
        check->setFlags(check->flags() | Qt::ItemIsUserCheckable);
        model->setItem(i, 0, check);
    }

    populateListView(quant, fileList, table);
}
/**
 * Populates a given table with a list of elements.
 * @brief Populates a given table.
 * @param quant The amount of items in the table.
 * @param fileList The list of items (in the case of DataWindow, filenames) from which the table is populated by.
 * @param table The table to be populated.
 * @see DataWindow::formatTable(int,QStringList)
 */
void DataWindow::populateListView(int quant, QStringList fileList, QTableView* table)
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
 * Creates a message box notifying the user of an error.
 * @brief Shows a failure message to the user.
 * @param message The message to be sent as an error.
 */
void DataWindow::showFailure(QString message)
{
    QMessageBox *msg = new QMessageBox;
    msg->setSizeIncrement(600, 400);
    msg->setText(message);
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

/**
 * Method called from when "OK" is pressed on the Data window.
 * Searches through indexes at column zero for checked boxes, and adds path to pathList.
 * @brief DataWindow::on_buttonBox_accepted
 */
void DataWindow::on_buttonBox_accepted()
{
    QStringList pathList;
    QString activePath;
    activePath = "";

    //Add selected paths to pathList
    for (int i = 0; i < model->rowCount(); i++) {
        QModelIndex index = model->index(i, 0, QModelIndex());

        if (index.data(Qt::CheckStateRole) == Qt::Checked){
            QModelIndex pathIndex = model->index(i, 1, QModelIndex());
            pathList.append(workingDir.absolutePath() +
                "/" + pathIndex.data().toString());
            qDebug() << pathList << " added to pathList";
        }

        //Identify active file
        index = model->index(i, 2, QModelIndex());

        if (index.data().toString() == "Active File") {
            index = model->index(i, 1, QModelIndex());
            activePath = workingDir.absolutePath() +
                "/" + index.data().toString();
        }
    }

    //Send file paths to parser
    if(pathList.isEmpty()) {
       showFailure("You didn't select any files!");
       on_buttonBox_rejected();
    } else if (activePath != "") {
        Parser::parse(pathList, activePath);
    } else {
        Parser::parse(pathList);
    }
}

/**
 * Method called when an index is double clicked.
 * Check the box in the first column upon double clicking any index in a row.
 * @brief DataWindow::on_fileListView_doubleClicked
 * @param index The index that has been double clicked.
 */
void DataWindow::on_fileListView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QModelIndex checkIndex = model->index(row, 0, QModelIndex());
    QStandardItem *item = new QStandardItem;
    item->setCheckable(true);
    item->setCheckState((checkIndex.data(Qt::CheckStateRole) == Qt::Checked) ? Qt::Unchecked : Qt::Checked);
    model->setItem(row, 0, item);
}

/**
 * Method called when "Set As Active File" clicked.
 * Changes status column of rows to reflect changes, and updates checkboxes.
 * @brief DataWindow::on_makeActiveButton_clicked
 */
void DataWindow::on_makeActiveButton_clicked()
{
    QModelIndexList indexes = table->selectionModel()->selectedIndexes();

    if (indexes.count() != 0){
        changeStatusColumn(indexes);
        updateCheckBoxes(indexes);
    }
}

/**
 * Changes the status column of rows accordingly.
 * @brief DataWindow::changeStatusColumn
 * @param indexes Selected indexes.
 */
void DataWindow::changeStatusColumn(QModelIndexList indexes){
    QModelIndex statusColIndex;

    for (int i = 0; i < model->rowCount(); i++) {
        statusColIndex = model->index(i, 2, QModelIndex());

        if (model->data(statusColIndex).toString() == "Active File") {
            QModelIndex fileName = model->index(i, 1, QModelIndex());

            if (model->data(fileName).toString().toLower().contains(".esm")) {
                model->setData(statusColIndex, "Master File");
            } else if (model->data(fileName).toString().toLower().contains(".esp")) {
                model->setData(statusColIndex, "Plugin File");
            }
        }
    }

    foreach (QModelIndex index, indexes) {
        if (index.column() == 2) {
            model->setData(index, "Active File");
        }
    }
}

/**
 * Updates the checkbox, if needed, of the active row.
 * @brief DataWindow::updateCheckBoxes
 * @param indexes Selected Indexes.
 */
void DataWindow::updateCheckBoxes(QModelIndexList indexes){
    QStandardItem *item = new QStandardItem;
    item->setCheckable(true);
    QModelIndex checkIndex = model->index(indexes[0].row(), 0, QModelIndex());

    if (checkIndex.data(Qt::CheckStateRole) == Qt::Unchecked){
        item->setCheckState(Qt::Checked);
        model->setItem(indexes[0].row(), 0, item);
    }
}
