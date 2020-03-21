#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

namespace Ui {
class mainwindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void actionData_triggered();
    void actionSave_triggered();
    void actionSettings_triggered();

private slots:
    void on_actionExit_triggered();
    void on_actionData_triggered();
    void on_actionOpenButton_triggered();
    void on_actionSave_triggered();
    void on_actionSaveButton_triggered();
    void on_actionSettings_triggered();

private:
    Ui::mainwindow *ui;
};

#endif //MAINWINDOW_H
