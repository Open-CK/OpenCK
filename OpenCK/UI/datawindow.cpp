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

void DataWindow::searchFiles()
{
    QDir dir = workingDir;
    dir.mkdir("Data");  //Note: this won't be called if the directory exists.
    dir.cd("./Data/");

    dir.setNameFilters(QStringList() << "*.esm" << "*.esp");
    QStringList fileList = dir.entryList();

    if (fileList.length() == 0){
        showFailure();
    }
    else{
        formatTable(fileList.count(), fileList);
    }
}

void DataWindow::formatTable(int quant, QStringList fileList)
{
    //Set up model headers and format
    QStandardItemModel *model = new QStandardItemModel(quant, 2, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Filename")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Status")));

    QTableView *table = ui->tableView;
    table->setModel(model);

    int width = table->width() / 2;
    table->setColumnWidth(0, width);
    table->setColumnWidth(1, ui->tableView->width() - width);
    table->verticalHeader()->hide();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    populateTable(quant, fileList, table);
}

void DataWindow::populateTable(int quant, QStringList fileList, QTableView* table)
{
    //Set up file names and status
    for (int i = 0; i < quant; i++){
        QString fileName = fileList[i];
        QModelIndex index = table->model()->index(i, 0);
        table->model()->setData(index, fileList[i]);

        QString type = fileName.split(".")[1];
        QString desc = "";
        index = table->model()->index(i, 1);

        if (type == "esm"){
            desc = "Master File";
        }
        else if (type == "esp"){
            desc = "Plugin File";
        }

        table->model()->setData(index, desc);
    }
}

void DataWindow::showFailure()
{
    QMessageBox *msg = new QMessageBox;
    msg->setSizeIncrement(600, 400);
    msg->setText("No *.esm or *.esp files were found.");
    msg->setStandardButtons(QMessageBox::Ok);
    msg->setIcon(QMessageBox::Critical);
    msg->exec();
}

DataWindow::~DataWindow()
{
    delete ui;
}

void DataWindow::on_buttonBox_rejected()
{
    close();
}
