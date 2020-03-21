#include "mainwindow.hpp"

#include "../../../ui/ui_mainwindow.h"

#include <QCoreApplication>

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

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionData_triggered()
{
    emit actionData_triggered();
}

void MainWindow::on_actionOpenButton_triggered()
{
    emit actionData_triggered();
}

void MainWindow::on_actionSave_triggered()
{
    emit actionSave_triggered();
}

void MainWindow::on_actionSaveButton_triggered()
{
    emit actionSave_triggered();
}

void MainWindow::on_actionSettings_triggered()
{
    emit actionSettings_triggered();
}
