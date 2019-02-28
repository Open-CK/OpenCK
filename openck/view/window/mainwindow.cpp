#include "mainwindow.h"

#include "../../../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionData_triggered()
{
    emit actionData_triggered();
}
