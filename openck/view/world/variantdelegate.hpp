#ifndef VARIANT_DELEGATE_H
#define VARIANT_DELEGATE_H

#include <QStyledItemDelegate>

class VariantDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    VariantDelegate(QObject* parent = nullptr);
    ~VariantDelegate();

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // VARIANT_DELEGATE_H