#ifndef GMSTDIALOG_H
#define GMSTDIALOG_H

#include "../world/variantdelegate.hpp"

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

    std::unique_ptr<VariantDelegateFactory> varTypeFactory;
    std::unique_ptr<GenericDelegate> varTypeDelegate;

    std::unique_ptr<EnumDelegateFactory> enumFactory;
    std::unique_ptr<GenericDelegate> modifiedDelegate;
};

#endif // GMSTDIALOG_H