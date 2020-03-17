#include "variantdelegate.hpp"

#include <QComboBox>

VariantDelegate::VariantDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{

}

VariantDelegate::~VariantDelegate()
{

}

QWidget* VariantDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QComboBox* combo = new QComboBox(parent);
    return combo;
}

void VariantDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QComboBox* comboBox = static_cast<QComboBox*>(editor);
    QString value = index.model()->data(index, Qt::EditRole).toString();
}

void VariantDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    
}
