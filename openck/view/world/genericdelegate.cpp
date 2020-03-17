#include "genericdelegate.hpp"

#include <QCheckBox>
#include <QItemEditorFactory>
#include <QPlainTextEdit>

TableModelHelper::TableModelHelper(QAbstractItemModel& model)
    : model(model)
{

}

int TableModelHelper::rowCount(const QModelIndex& parent) const
{
    return model.rowCount(parent);
}

int TableModelHelper::columnCount(const QModelIndex& parent) const
{
    return model.columnCount(parent);
}

QVariant TableModelHelper::data(const QModelIndex& index, int role) const
{
    return model.data(index, role);
}

bool TableModelHelper::setData(const QModelIndex& index, const QVariant& value, int role)
{
    modelData = value;

    return true;
}

QVariant TableModelHelper::getData() const
{
    return modelData;
}

GenericDelegate::GenericDelegate(Document& document, QObject* parent) :
    QStyledItemDelegate(parent),
    isLocked(false),
    document(document)
{

}

void GenericDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (!isLocked)
    {
        setModelDataImp(editor, model, index);
    }
}

QWidget* GenericDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    BaseColumn::Display display = getDisplayTypeFromIndex(index);

    if (display == BaseColumn::Display_Boolean)
    {
        return QItemEditorFactory::defaultFactory()->createEditor(QVariant::Bool, parent);
    }

    return createEditor(parent, option, index, display);
}

QWidget* GenericDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index, BaseColumn::Display display) const
{
    QVariant variant = index.data();

    if (!variant.isValid())
    {
        variant = index.data(Qt::DisplayRole);

        if (!variant.isValid())
        {
            return 0;
        }
    }

    switch (display)
    {
        case BaseColumn::Display_LongString:
        {
            QPlainTextEdit* edit = new QPlainTextEdit(parent);
            edit->setUndoRedoEnabled(false);
            return edit;
        }
        case BaseColumn::Display_Boolean:
        {
            return new QCheckBox(parent);
        }
        default:
        {
            return QStyledItemDelegate::createEditor(parent, option, index);
        }
    }
}

void GenericDelegate::setEditLock(bool locked)
{
    isLocked = locked;
}

bool GenericDelegate::isEditLocked() const
{
    return isLocked;
}

void GenericDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    setEditorData(editor, index, false);
}

void GenericDelegate::setEditorData(QWidget* editor, const QModelIndex& index, bool tryDisplay) const
{
    QVariant variant = index.data(Qt::EditRole);

    if (tryDisplay)
    {
        if (!variant.isValid())
        {
            variant = index.data(Qt::DisplayRole);

            if (!variant.isValid())
            {
                return;
            }
        }

        QPlainTextEdit* edit = qobject_cast<QPlainTextEdit*>(editor);

        if (edit)
        {
            if (edit->toPlainText() == variant.toString())
            {
                return;
            }
        }
    }
}

Document& GenericDelegate::getDocument() const
{
    return document;
}

BaseColumn::Display GenericDelegate::getDisplayTypeFromIndex(const QModelIndex& index) const
{
    int raw = index.data(BaseColumn::Role_Display).toInt();
    
    return static_cast<BaseColumn::Display>(raw);
}

void GenericDelegate::setModelDataImp(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QVariant variant;

    TableModelHelper helper(*model);
    QStyledItemDelegate::setModelData(editor, &helper, index);
    variant = helper.getData();

    if (model->data(index) != variant && model->flags(index) & Qt::ItemIsEditable)
    {
        // Modify record
    }
}
