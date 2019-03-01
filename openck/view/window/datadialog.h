#ifndef DATADIALOG_H
#define DATADIALOG_H

#include "../../model/window/datatable.h"

#include <QDialog>
#include <QTableView>

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

private:
    QTableView* tableView();

    std::unique_ptr<DataTable> dataTable;
    Ui::datadialog *ui;
};

#endif // DATADIALOG_H
