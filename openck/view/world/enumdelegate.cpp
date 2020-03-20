#include "enumdelegate.hpp"

#include <QApplication>
#include <QComboBox>

EnumDelegateFactory::EnumDelegateFactory()
{

}

EnumDelegateFactory::EnumDelegateFactory(ColumnId column)
{
    if (Columns::hasNames(column))
    {
        QString* names = Columns::getEnumNames(column);

        for (int i = 0; names[i] != 0; i++)
        {
            values.push_back(QPair<int, QString>(i, names[i]));
        }
    }
}

EnumDelegateFactory::~EnumDelegateFactory()
{

}

GenericDelegate* EnumDelegateFactory::makeDelegate(Document& document, QObject* parent) const
{
    return new EnumDelegate(values, document, parent);
}

EnumDelegate::EnumDelegate(const QVector<QPair<int, QString>>& values, Document& document, QObject* parent) :
    GenericDelegate(document, parent),
    values(values)
{

}

QWidget* EnumDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return createEditor(parent, option, index, BaseColumn::Display_None);
}

QWidget* EnumDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index, BaseColumn::Display display) const
{
    if (!index.data(Qt::EditRole).isValid() && !index.data(Qt::DisplayRole).isValid())
    {
        return nullptr;
    }

    QComboBox* comboBox = new QComboBox(parent);

    for (const auto& value : values)
    {
        comboBox->addItem(value.second);
    }

    return comboBox;
}

void EnumDelegate::setEditorData(QWidget* editor, const QModelIndex& index, bool tryDisplay) const
{
    if (QComboBox* comboBox = dynamic_cast<QComboBox*>(editor))
    {
        int role = Qt::EditRole;

        if (tryDisplay && !index.data(role).isValid())
        {
            role = Qt::DisplayRole;

            if (!index.data(role).isValid())
            {
                return;
            }
        }

        int valueIndex = getValueIndex(index, role);

        if (valueIndex != -1)
        {
            comboBox->setCurrentIndex(valueIndex);
        }
    }
}

void EnumDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int valueIndex = getValueIndex(index);

    if (valueIndex != -1)
    {
        QStyleOptionViewItem itemOption(option);

        itemOption.text = values.at(valueIndex).second;

        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &itemOption, painter);
    }
}

QSize EnumDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    int valueIndex = getValueIndex(index);

    if (valueIndex != -1)
    {
        QStyleOptionComboBox itemOption;
        
        itemOption.fontMetrics = option.fontMetrics;
        itemOption.palette = option.palette;
        itemOption.rect = option.rect;
        itemOption.state = option.state;

        const QString& valueText = values.at(valueIndex).second;
        QSize valueSize = QSize(itemOption.fontMetrics.width(valueText), itemOption.fontMetrics.height());

        itemOption.currentText = valueText;

        return QApplication::style()->sizeFromContents(QStyle::CT_ComboBox, &itemOption, valueSize);
    }

    return option.rect.size();
}

void EnumDelegate::setModelDataImp(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (QComboBox * comboBox = dynamic_cast<QComboBox*>(editor))
    {
        QString value = comboBox->currentText();

        for (const auto currValue : values)
        {
            if (currValue.second == value)
            {
                if (model->data(index).toInt() != currValue.first)
                {
                    // Command stuff to come
                    break;
                }
            }
        }
    }
}

int EnumDelegate::getValueIndex(const QModelIndex& index, int role) const
{
    if (index.isValid() && index.data(role).isValid())
    {
        int value = index.data(role).toInt();

        for (int i = 0; i < values.size(); i++)
        {
            if (value == values.at(i).first)
            {
                return  i;
            }
        }
    }

    return -1;
}
