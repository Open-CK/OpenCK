#ifndef DATADIALOG_H
#define DATADIALOG_H

#include "../doc/loader.hpp"
#include "../../model/window/datatable.hpp"
#include "../../model/window/masterslist.hpp"

#include <QDialog>
#include <QLabel>
#include <QListView>
#include <QPlainTextEdit>
#include <QTableView>
#include <QVBoxLayout>

#include <memory>

namespace Ui {
class datadialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    DataDialog(QWidget *parent = nullptr);
    ~DataDialog();

    void setUp(const QString& path);

public slots:
    void newSelection(const QModelIndex& current, const QModelIndex& previous);

private:
    void configureTable();
    void configureList();

    QTableView* tableView();
    QLineEdit* authorLineEdit();
    QPlainTextEdit* descriptionTextEdit();
    QListView* mastersView();
    QLabel* createdLabel();
    QLabel* modifiedLabel();
    QPushButton* activeButton();

    QString dataPath;
    std::unique_ptr<DataTable> dataTable;
    std::unique_ptr<MastersList> mastersList;
    Ui::datadialog *ui;

    LoaderView loader;

private slots:
    void on_activeButton_clicked();
    void accept() override;

signals:
    void addDocument(const QStringList& files, const QString& savePath, bool isNew);
};

#endif // DATADIALOG_H
