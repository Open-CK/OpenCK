#ifndef DATADIALOG_H
#define DATADIALOG_H

#include "../../model/window/datatable.h"

#include <QDialog>
#include <QListView>
#include <QTableView>
#include <QPlainTextEdit>

#include <memory>

namespace Ui {
class datadialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = nullptr);
    ~DataDialog();

    void setUp(const QString& dataPath);

public slots:
    void newSelection(const QModelIndex& current, const QModelIndex& previous);

private:
    QTableView* tableView();
    QLineEdit* authorLineEdit();
    QPlainTextEdit* descriptionTextEdit();
    QListView* masterView();

    std::unique_ptr<DataTable> dataTable;
    Ui::datadialog *ui;
};

#endif // DATADIALOG_H
