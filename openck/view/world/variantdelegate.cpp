#include "variantdelegate.hpp"
#include "../../model/world/columns.hpp"

#include <QComboBox>

VariantDelegateFactory::VariantDelegateFactory()
{
    values = Columns::getEnums(ColumnId::ColumnId_ValueType);
}

VariantDelegateFactory::~VariantDelegateFactory()
{

}

GenericDelegate* VariantDelegateFactory::makeDelegate(Document& document, QObject* parent) const
{
    return new VariantDelegate(values, document, parent);
}

VariantDelegate::VariantDelegate(const QVector<QPair<int, QString>>& values, Document& document, QObject* parent) :
    EnumDelegate(values, document, parent)
{
    
}
