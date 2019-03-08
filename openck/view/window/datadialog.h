#ifndef DATADIALOG_H
#define DATADIALOG_H

#include "../../model/window/datatable.h"
#include "../../model/window/masterslist.h"

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
    explicit DataDialog(QWidget *parent = nullptr);
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

private slots:
    void on_activeButton_clicked();
    void accept() override;

signals:
    void newDocument(QStringList files, bool isNew);
};

#endif // DATADIALOG_H
