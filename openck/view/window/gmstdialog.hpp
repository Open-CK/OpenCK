#ifndef GMSTDIALOG_H
#define GMSTDIALOG_H

#include <QDialog>

class Document;

namespace Ui {
class gmstdialog;
}

class GmstDialog : public QDialog
{
    Q_OBJECT

public:
    GmstDialog(QWidget* parent = nullptr);
    ~GmstDialog();

    void setUp(Document* document);

private:
    Ui::gmstdialog* ui;
};

#endif // GMSTDIALOG_H